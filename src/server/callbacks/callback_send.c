/*
** EPITECH PROJECT, 2021
** CALLBACK_SEND
** File description:
** Callback send
*/

#include "wrapper_logging_server.h"

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

static void reply_to_cmd(
    teams_server_t *teams_server, teams_client_t *teams_client, message_t *pm)
{
    SERVER_EVENT_PRIVATE_MESSAGE_SENDED(pm->from, pm->to, pm->message);
    tc_send_packet_info_msg(teams_client, pm->from, pm->timestamp, pm->message);
    ts_send_event_new_msg(teams_server, pm);
}

ns_status_e callback_send(teams_server_t *teams_server,
    teams_client_t *teams_client, const struct cli_pck_send *packet)
{
    message_t pm = { 0 };
    json_object_t *user;

    user = db_get_user_by_id(teams_server->database, packet->user_uuid);
    if (!user) {
        tc_send_packet_uuid_not_found(
            teams_client, USER_NOT_FOUND, packet->user_uuid);
        return NS_OK;
    }
    copy_uuid(pm.from, teams_client->uuid);
    copy_uuid(pm.to, packet->user_uuid);
    exctract_body_from_packet(pm.message, packet->msg);
    if (!db_add_private_message(teams_server->database, &pm)) {
        tc_send_packet_error(teams_client, ERR_INTERNAL);
        return NS_OK;
    }
    reply_to_cmd(teams_server, teams_client, &pm);
    return NS_OK;
}