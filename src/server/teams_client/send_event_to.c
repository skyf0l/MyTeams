/*
** EPITECH PROJECT, 2021
** SEND_EVENT_TO
** File description:
** Send_event_to function
*/

#include <string.h>

#include "list/list.h"

#include "server/database.h"
#include "server/teams_client.h"
#include "server/teams_server.h"

int ts_send_event_to_user(
    teams_server_t *teams_server, const uuid_t user_uuid, const void *raw_event)
{
    list_t *user_lists = teams_server->net_server->clients;
    teams_client_t *teams_client;
    int nb_user_send = 0;

    LIST_ITERATE(it, user_lists)
    {
        if (!it->data)
            continue;
        teams_client = ((net_client_t *) it->data)->custom_data;
        if (teams_client && teams_client->is_logged
            && memcmp(teams_client->uuid, user_uuid, sizeof(uuid_t)) == 0) {
            tc_send_event(teams_client, raw_event);
            nb_user_send += 1;
        }
    }
    return nb_user_send;
}

int ts_send_event_to_all_other_users(teams_server_t *teams_server,
    teams_client_t *teams_client, const void *raw_event)
{
    list_t *user_lists = teams_server->net_server->clients;
    teams_client_t *tmp_teams_client;
    int nb_user_send = 0;

    LIST_ITERATE(it, user_lists)
    {
        if (!it->data)
            continue;
        tmp_teams_client = ((net_client_t *) it->data)->custom_data;
        if (tmp_teams_client && tmp_teams_client->is_logged
            && tmp_teams_client != teams_client) {
            tc_send_event(tmp_teams_client, raw_event);
            nb_user_send += 1;
        }
    }
    return nb_user_send;
}

int ts_send_event_to_all_users(
    teams_server_t *teams_server, const void *raw_event)
{
    list_t *user_lists = teams_server->net_server->clients;
    teams_client_t *teams_client;
    int nb_user_send = 0;

    LIST_ITERATE(it, user_lists)
    {
        if (!it->data)
            continue;
        teams_client = ((net_client_t *) it->data)->custom_data;
        if (teams_client && teams_client->is_logged) {
            tc_send_event(teams_client, raw_event);
            nb_user_send += 1;
        }
    }
    return nb_user_send;
}

int ts_send_event_to_sub_users(
    teams_server_t *teams_server, const uuid_t team_uuid, const void *raw_event)
{
    json_object_t *team = db_get_chat_by_id(
        json_object_get_object(teams_server->database, "teams"), team_uuid);
    json_array_t *users_sub = json_object_get_array(team, "users_sub");
    int nb_user_send = 0;
    uuid_t user_uuid;

    JSON_ARRAY_ITERATE(it, id, users_sub)
    {
        if (!json_it_get_string(it))
            continue;
        uuid_parse(json_it_get_string(it), user_uuid);
        nb_user_send +=
            ts_send_event_to_user(teams_server, user_uuid, raw_event);
    }
    return 0;
}