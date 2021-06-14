/*
** EPITECH PROJECT, 2021
** RUN_TEAMS_SERVER
** File description:
** Run_teams_server function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myteams/logging_server.h"
#include "net/net_server.h"

#include "tools.h"

#include "server/server_core.h"
#include "server/teams_server.h"

static net_server_t *create_teams_server(int port)
{
    net_server_t *net_server = ns_create(AF_INET, SOCK_STREAM, port);
    teams_server_t *teams_server;

    if (!net_server) {
        printf("Can not create net_server\n");
        return NULL;
    }
    teams_server = teams_server_create(net_server);
    if (!teams_server) {
        ns_destroy(net_server);
        return NULL;
    }
    net_server->custom_data = teams_server;
    net_server->custom_destructor = (void *(*) (void *) ) teams_server_destroy;
    ns_set_callbacks(net_server, net_server_callbacks);
    return net_server;
}

int run_teams_server(int port)
{
    net_server_t *net_server = create_teams_server(port);

    if (!net_server) {
        printf("Can not create teams_server\n");
        return EXIT_FAILURE;
    }
    if (!ns_run(net_server)) {
        ns_destroy(net_server);
        return EXIT_FAILURE;
    }
    ns_destroy(net_server);
    return EXIT_SUCCESS;
}