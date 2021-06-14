/*
** EPITECH PROJECT, 2021
** CALLBACK_CREATE_REPLY
** File description:
** Callback create_reply
*/

#include "wrapper_logging_server.h"

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

static bool can_create_reply(teams_server_t *server, teams_client_t *client,
    const struct cli_pck_create_reply *packet)
{
    json_object_t *thread;

    if (!(thread = db_get_team_by_uuid(server->database, packet->team_uuid))) {
        tc_send_packet_uuid_not_found(
            client, TEAM_NOT_FOUND, packet->team_uuid);
        return false;
    }
    if (!(thread = db_get_channel_by_uuid(thread, packet->chan_uuid))) {
        tc_send_packet_uuid_not_found(
            client, CHAN_NOT_FOUND, packet->chan_uuid);
        return false;
    }
    if (!(thread = db_get_thread_by_uuid(thread, packet->thread_uuid))) {
        tc_send_packet_uuid_not_found(
            client, THREAD_NOT_FOUND, packet->thread_uuid);
        return false;
    }
    return true;
}

static void send_new_reply(teams_server_t *server, teams_client_t *client,
    const struct cli_pck_create_reply *packet, message_t *message_infos)
{
    SERVER_EVENT_REPLY_CREATED(
        packet->thread_uuid, client->uuid, message_infos->message);
    tc_send_packet_info_reply(
        client, packet->team_uuid, packet->thread_uuid, message_infos);
    ts_send_event_new_reply(
        server, packet->team_uuid, packet->thread_uuid, message_infos);
}

ns_status_e callback_create_reply(teams_server_t *server,
    teams_client_t *client, const struct cli_pck_create_reply *packet)
{
    message_t message_infos = { 0 };
    msg_location_t location = { 0 };

    if (!db_is_sub_to_team(server->database, client->uuid, packet->team_uuid)) {
        tc_send_packet_error(client, ERR_NO_PERM);
        return NS_OK;
    }
    if (!can_create_reply(server, client, packet))
        return NS_OK;
    copy_uuid(message_infos.from, client->uuid);
    exctract_body_from_packet(message_infos.message, packet->reply_msg);
    copy_uuid(location.team_uuid, packet->team_uuid);
    copy_uuid(location.channel_uuid, packet->chan_uuid);
    copy_uuid(location.thread_uuid, packet->thread_uuid);
    if (!db_add_message(server->database, &location, &message_infos)) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return NS_OK;
    }
    send_new_reply(server, client, packet, &message_infos);
    return NS_OK;
}
