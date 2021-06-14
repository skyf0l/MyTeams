/*
** EPITECH PROJECT, 2021
** NET_SERVER_RUN
** File description:
** Net_server_run function
*/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "list.h"

#include "interval.h"

#include "net_server.h"
#include "net_socket.h"

static void ns_close_all_sockets(net_server_t *net_server)
{
    printf("Exit server on port: %d, close all sockets...\n",
        ntohs(net_server->addr.sa_in.sin_port));
    list_clear(net_server->clients);
}

static void ns_accept_new_client(net_server_t *net_server, int socket_fd)
{
    int new_socket;
    socklen_t addr_len = sizeof(sockaddr_t);
    sockaddr_t addr;
    net_client_t *client = NULL;

    new_socket = accept(socket_fd, (struct sockaddr *) &addr, &addr_len);
    if (new_socket == -1) {
        perror("Accept failed");
        return;
    }
    client = nc_create(net_server, new_socket);
    if (!client) {
        fprintf(stderr, "Can not create net_client: memory exhausted\n");
        close_socket(new_socket);
        return;
    }
    ns_add_client(net_server, client);
    FD_SET(new_socket, &net_server->need_read_fds);
    extend_interval(&net_server->socket_interval, new_socket);
    NS_CALLBACK(net_server, on_accept, client);
}

static void ns_run_ready_socket(net_server_t *net_server, int socket_fd)
{
    net_client_t *client = NULL;

    if (socket_fd == net_server->socket)
        ns_accept_new_client(net_server, socket_fd);
    else {
        client = ns_get_client(net_server, socket_fd);
        NS_CALLBACK(net_server, on_ready, client);
    }
}

static void process_fds(
    net_server_t *net_server, fd_set *read_fds, fd_set *write_fds)
{
    net_client_t *net_client = NULL;

    FOREACH_SOCKET(fd, net_server->socket_interval, write_fds) {
        net_client = ns_get_client(net_server, fd);
        if (net_client->disconnected && net_client->write_buffer.length == 0) {
            ns_remove_client(net_server, net_client);
            continue;
        }
        if (nc_flush(net_client) == -1) {
            ns_remove_client(net_server, net_client);
        } else if (net_client->disconnected
            && net_client->write_buffer.length == 0) {
            ns_remove_client(net_server, net_client);
            continue;
        }
    }
    FOREACH_SOCKET(fd, net_server->socket_interval, read_fds) {
        ns_run_ready_socket(net_server, fd);
    }
}

bool ns_run(net_server_t *ns)
{
    ns->running = true;
    printf("Run server on port: %d\n", ntohs(ns->addr.sa_in.sin_port));
    FD_ZERO(&ns->need_read_fds);
    FD_ZERO(&ns->need_write_fds);
    FD_SET(ns->socket, &ns->need_read_fds);
    while (ns->running) {
        memcpy(&ns->read_fds, &ns->need_read_fds, sizeof(fd_set));
        memcpy(&ns->write_fds, &ns->need_write_fds, sizeof(fd_set));
        if (select(FD_SETSIZE, &ns->read_fds, &ns->write_fds, NULL, NULL)
            == -1) {
            printf("Select failed: %s\n", strerror(errno));
            break;
        }
        process_fds(ns, &ns->read_fds, &ns->write_fds);
    }
    ns_close_all_sockets(ns);
    return true;
}