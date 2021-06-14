/*
** EPITECH PROJECT, 2021
** CALLBACK_MESSAGES
** File description:
** Callback messages
*/

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

static void send_message(teams_client_t *client, json_it_t *it)
{
    json_object_t *message = json_it_get_object(it);
    char *sender_uuid_str = json_object_get_string(message, "from");
    time_t msg_timestamp = json_object_get_long(message, "timestamp");
    char *msg = json_object_get_string(message, "message");
    uuid_t sender_uuid;

    if (!message || !sender_uuid_str || !msg
        || uuid_parse(sender_uuid_str, sender_uuid) == -1) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return;
    };
    tc_send_packet_info_msg(client, sender_uuid, msg_timestamp, msg);
}

static void send_messages(teams_client_t *client, json_object_t *msgs)
{
    tc_send_packet_list_header(
        client, msgs->elements_count, SERV_ID_INFO_MESSAGE);
    JSON_OBJECT_ITERATE(it, msgs)
    {
        send_message(client, it);
    }
}

ns_status_e callback_messages(teams_server_t *server,
    teams_client_t *teams_client, const struct cli_pck_messages *packet)
{
    json_object_t *pm;
    json_object_t *msgs;

    if (!db_get_user_by_id(server->database, packet->user_uuid)) {
        tc_send_packet_uuid_not_found(
            teams_client, USER_NOT_FOUND, packet->user_uuid);
        return NS_OK;
    }
    pm = db_get_pm_by_user_id(
        server->database, teams_client->uuid, packet->user_uuid);
    msgs = json_object_get_object(pm, "messages");
    if (!pm || !msgs)
        tc_send_packet_list_header(teams_client, 0, SERV_ID_INFO_MESSAGE);
    else
        send_messages(teams_client, msgs);
    return NS_OK;
}
