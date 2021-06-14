/*
** EPITECH PROJECT, 2021
** NET_SERVER
** File description:
** Net_server function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

#include "get_next_something.h"

#include "net_client.h"
#include "net_server.h"
#include "net_socket.h"

static void nc_destroy_no_rt(net_client_t *client)
{
    nc_destroy(client);
}

net_server_t *ns_create(sa_family_t domain, int type, uint16_t port)
{
    net_server_t *net_server = malloc(sizeof(net_server_t));

    if (!net_server)
        return NULL;
    memset(net_server, 0, sizeof(net_server_t));
    net_server->socket = create_socket(domain, type);
    if (setsockopt(net_server->socket, SOL_SOCKET, SO_REUSEADDR, (int[1]){1},
        sizeof(int)) == -1)
        perror("Setsockopt failed");
    if (net_server->socket == -1)
        return ns_destroy(net_server);
    net_server->socket_interval.from = net_server->socket;
    net_server->socket_interval.to = net_server->socket;
    net_server->socket_interval.to_included = true;
    net_server->clients = list_create((void (*)(void *))nc_destroy_no_rt);
    if (!bind_socket(net_server->socket, domain, port, &net_server->addr) ||
        !listen_socket(net_server->socket) || !net_server->clients)
        return ns_destroy(net_server);
    return net_server;
}

void *ns_destroy(net_server_t *net_server)
{
    if (!net_server)
        return NULL;
    if (net_server->socket != -1)
    {
        if (shutdown(net_server->socket, SHUT_RDWR) == -1)
            perror("Shutdown failed");
        close_socket(net_server->socket);
    }
    if (net_server->clients)
        list_destroy(net_server->clients);
    if (net_server->custom_data && net_server->custom_destructor)
        net_server->custom_destructor(net_server->custom_data);
    gns_clear_sockets();
    free(net_server);
    return NULL;
}