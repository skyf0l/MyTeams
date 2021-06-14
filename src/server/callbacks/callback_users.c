/*
** EPITECH PROJECT, 2021
** CALLBACK_USERS
** File description:
** Callback users
*/

#include "json/json.h"

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

static void send_user(
    teams_server_t *server, teams_client_t *client, json_it_t *it)
{
    json_object_t *user = json_it_get_object(it);
    char *key = json_it_get_key(it);
    char *username;
    uuid_t uuid;

    if (!user || !key) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return;
    }
    username = json_object_get_string(user, "name");
    uuid_parse(key, uuid);
    tc_send_packet_info_user(
        client, uuid, username, db_is_user_logged_in(server->database, uuid));
}

ns_status_e callback_users(teams_server_t *server, teams_client_t *client,
    const struct cli_pck_users *packet)
{
    json_object_t *users = json_object_get_object(server->database, "users");

    UNUSED(packet);
    if (!users) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return NS_OK;
    }
    tc_send_packet_list_header(
        client, users->elements_count, SERV_ID_INFO_USER);
    JSON_OBJECT_ITERATE(it, users)
    {
        send_user(server, client, it);
    }
    return NS_OK;
}
