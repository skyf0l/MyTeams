/*
** EPITECH PROJECT, 2021
** CALLBACKS
** File description:
** Callbacks function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "net/gns/get_next_packet.h"

#include "tools.h"

#include "server/server_core.h"
#include "server/teams_client.h"
#include "server/teams_server.h"

ns_status_e on_accept(net_server_t *net_server, net_client_t *net_client)
{
    teams_server_t *teams_server = (teams_server_t *) net_server->custom_data;
    teams_client_t *teams_client = teams_client_create(net_client);

    UNUSED(net_server), UNUSED(net_client);
    if (!teams_client) {
        printf("Can not create teams_client: memory exhausted\n");
        return NS_CLOSE_CLIENT;
    }
    net_client->custom_data = teams_client;
    net_client->custom_destructor = (void *(*) (void *) ) teams_client_destroy;
    teams_client->server = teams_server;
    return on_client_connect(teams_server, teams_client);
}

ns_status_e on_ready_loop(net_server_t *net_server, net_client_t *net_client)
{
    teams_server_t *teams_server = (teams_server_t *) net_server->custom_data;
    teams_client_t *teams_client = (teams_client_t *) net_client->custom_data;
    ns_status_e return_value = NS_OK;
    struct pck *packet;

    packet = gnp_extract_next_packet(net_client->socket);
    if (!packet)
        return NS_OK;
    return_value = on_client_recv_packet(teams_server, teams_client, packet);
    free(packet);
    if (return_value == NS_OK)
        return on_ready_loop(net_server, net_client);
    return return_value;
}

ns_status_e on_ready(net_server_t *net_server, net_client_t *net_client)
{
    teams_server_t *teams_server = (teams_server_t *) net_server->custom_data;
    teams_client_t *teams_client = (teams_client_t *) net_client->custom_data;
    ns_status_e return_value = NS_OK;
    int read_len;
    struct pck *packet;

    packet = gnp(net_client->socket, &read_len);
    if (read_len <= 0) {
        if (packet)
            free(packet);
        return (read_len == -1) ? NS_CLOSE_CLIENT : NS_DISCONNECT_CLIENT;
    }
    if (!packet)
        return NS_OK;
    return_value = on_client_recv_packet(teams_server, teams_client, packet);
    free(packet);
    if (return_value == NS_OK)
        return on_ready_loop(net_server, net_client);
    return return_value;
}

ns_status_e on_disconnect(net_server_t *net_server, net_client_t *net_client)
{
    teams_server_t *teams_server = (teams_server_t *) net_server->custom_data;
    teams_client_t *teams_client = (teams_client_t *) net_client->custom_data;

    return on_client_disconnect(teams_server, teams_client);
}

void on_close(net_server_t *net_server, net_client_t *net_client)
{
    teams_server_t *teams_server = (teams_server_t *) net_server->custom_data;
    teams_client_t *teams_client = (teams_client_t *) net_client->custom_data;

    on_client_close(teams_server, teams_client);
}