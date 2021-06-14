/*
** EPITECH PROJECT, 2021
** TEAMS_CLIENT
** File description:
** Teams_client function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "net/net_server.h"

#include "tools.h"

#include "server/teams_client.h"

teams_client_t *teams_client_create(net_client_t *net_client)
{
    teams_client_t *teams_client = malloc(sizeof(teams_client_t));

    if (!teams_client)
        return NULL;
    memset(teams_client, 0, sizeof(teams_client_t));
    teams_client->net_client = net_client;
    teams_client->is_logged = false;
    return teams_client;
}

void *teams_client_destroy(teams_client_t *teams_client)
{
    if (!teams_client)
        return NULL;
    free(teams_client);
    return NULL;
}