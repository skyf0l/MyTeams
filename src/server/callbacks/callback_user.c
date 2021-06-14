/*
** EPITECH PROJECT, 2021
** CALLBACK_USER
** File description:
** Callback user
*/

#include "json/json.h"

#include "teams.h"
#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

ns_status_e callback_user(teams_server_t *teams_server,
    teams_client_t *teams_client, const struct cli_pck_user *packet)
{
    json_object_t *user;

    user = db_get_user_by_id(teams_server->database, packet->user_uuid);
    if (!user) {
        tc_send_packet_uuid_not_found(
            teams_client, USER_NOT_FOUND, packet->user_uuid);
        return NS_OK;
    }
    tc_send_packet_info_user(teams_client, packet->user_uuid,
        json_object_get_string(user, "name"),
        db_is_user_logged_in(teams_server->database, packet->user_uuid));
    return NS_OK;
}
