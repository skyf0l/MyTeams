/*
** EPITECH PROJECT, 2021
** CALLBACK_LIST_REPLIES
** File description:
** Callback list_replies
*/

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

static void send_reply(teams_client_t *client, json_it_t *reply_it,
    const uuid_t team_uuid, const uuid_t thread_uuid)
{
    message_t reply_infos = { 0 };
    json_object_t *reply = json_it_get_object(reply_it);
    char *sender_uuid = json_object_get_string(reply, "from");
    char *message = json_object_get_string(reply, "message");

    reply_infos.timestamp = json_object_get_long(reply, "timestamp");
    if (!reply || !sender_uuid || !message
        || uuid_parse(sender_uuid, reply_infos.from) == -1) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return;
    }
    exctract_body_from_packet(reply_infos.message, message);
    tc_send_packet_info_reply(client, team_uuid, thread_uuid, &reply_infos);
}

static json_object_t *found_replies(json_object_t *database,
    teams_client_t *client, const struct cli_pck_list_replies *pck)
{
    json_object_t *replies = db_get_team_by_uuid(database, pck->team_uuid);

    if (!replies) {
        tc_send_packet_uuid_not_found(client, TEAM_NOT_FOUND, pck->team_uuid);
        return NULL;
    }
    if (!(replies = db_get_channel_by_uuid(replies, pck->chan_uuid))) {
        tc_send_packet_uuid_not_found(client, CHAN_NOT_FOUND, pck->chan_uuid);
        return NULL;
    }
    if (!(replies = db_get_thread_by_uuid(replies, pck->thread_uuid))) {
        tc_send_packet_uuid_not_found(
            client, THREAD_NOT_FOUND, pck->thread_uuid);
        return NULL;
    }
    if (!(replies = json_object_get_object(replies, "messages"))) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return NULL;
    }
    return replies;
}

ns_status_e callback_list_replies(teams_server_t *server,
    teams_client_t *client, const struct cli_pck_list_replies *packet)
{
    json_object_t *replies = found_replies(server->database, client, packet);

    if (!replies)
        return NS_OK;
    tc_send_packet_list_header(
        client, replies->elements_count, SERV_ID_INFO_REPLY);
    JSON_OBJECT_ITERATE(it, replies)
    {
        send_reply(client, it, packet->team_uuid, packet->thread_uuid);
    }
    return NS_OK;
}
