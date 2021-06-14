/*
** EPITECH PROJECT, 2021
** TEAMS_SERVER
** File description:
** Teams_server function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "myteams/logging_server.h"

#include "net/net_server.h"
#include "json/json.h"

#include "teams.h"
#include "tools.h"

#include "server/database.h"
#include "server/teams_client.h"
#include "server/teams_server.h"

static void load_all_users_of_db(json_object_t *database)
{
    json_object_t *users = json_object_get_object(database, "users");
    json_object_t *user;

    if (!users)
        return;
    JSON_OBJECT_ITERATE(it, users)
    {
        user = json_it_get_object(it);
        server_event_user_loaded(
            json_it_get_key(it), json_object_get_string(user, "name"));
        json_object_remove(user, "status");
    }
}

teams_server_t *teams_server_create(net_server_t *net_server)
{
    teams_server_t *teams_server = malloc(sizeof(teams_server_t));

    if (!teams_server)
        return NULL;
    memset(teams_server, 0, sizeof(teams_server_t));
    teams_server->net_server = net_server;
    teams_server->database = db_load(DATABASE_PATH, EMPTY_DATABASE);
    teams_server->start_time = time(NULL);
    if (!teams_server->database)
        return teams_server_destroy(teams_server);
    load_all_users_of_db(teams_server->database);
    return teams_server;
}

void *teams_server_destroy(teams_server_t *teams_server)
{
    if (!teams_server)
        return NULL;
    if (teams_server->database) {
        json_object_save_to_file(teams_server->database, DATABASE_PATH);
        json_object_destroy(teams_server->database);
    }
    free(teams_server);
    return NULL;
}