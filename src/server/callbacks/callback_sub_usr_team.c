/*
** EPITECH PROJECT, 2021
** CALLBACK_SUB_USR_TEAM
** File description:
** Callback sub_usr_team
*/

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

static void send_sub_usr_team(
    teams_server_t *server, teams_client_t *client, json_it_t *user_sub_it)
{
    json_object_t *user;
    uuid_t user_uuid;

    if (!json_it_get_string(user_sub_it)
        || uuid_parse(json_it_get_string(user_sub_it), user_uuid) == -1) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return;
    }
    user = db_get_user_by_id(server->database, user_uuid);
    if (!user || !json_object_get_string(user, "name")) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return;
    }
    tc_send_packet_info_user(client, user_uuid,
        json_object_get_string(user, "name"),
        !!json_object_get_int(user, "status"));
}

ns_status_e callback_sub_usr_team(teams_server_t *teams_server,
    teams_client_t *teams_client, const struct cli_pck_sub_usr_team *packet)
{
    json_object_t *team =
        db_get_team_by_uuid(teams_server->database, packet->team_uuid);
    json_array_t *users_sub = json_object_get_array(team, "users_sub");

    if (!team) {
        tc_send_packet_uuid_not_found(
            teams_client, TEAM_NOT_FOUND, packet->team_uuid);
        return NS_OK;
    }
    if (!users_sub) {
        tc_send_packet_error(teams_client, ERR_INTERNAL);
        return NS_OK;
    }
    tc_send_packet_list_header(
        teams_client, users_sub->elements_count, SERV_ID_INFO_USER);
    JSON_ARRAY_ITERATE(it, id, users_sub)
    {
        send_sub_usr_team(teams_server, teams_client, it);
    }
    return NS_OK;
}
