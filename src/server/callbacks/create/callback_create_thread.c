/*
** EPITECH PROJECT, 2021
** CALLBACK_CREATE_THREAD
** File description:
** Callback create_thread
*/

#include "wrapper_logging_server.h"

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

static bool can_create_thread(teams_server_t *server, teams_client_t *client,
    const struct cli_pck_create_thread *packet)
{
    json_object_t *chat;
    char thread_title[MAX_NAME_LENGTH];

    if (!(chat = db_get_team_by_uuid(server->database, packet->team_uuid))) {
        tc_send_packet_uuid_not_found(
            client, TEAM_NOT_FOUND, packet->team_uuid);
        return false;
    }
    if (!(chat = db_get_channel_by_uuid(chat, packet->chan_uuid))) {
        tc_send_packet_uuid_not_found(
            client, CHAN_NOT_FOUND, packet->chan_uuid);
        return false;
    }
    exctract_name_from_packet(thread_title, packet->thread_title);
    if (db_get_thread_by_name(chat, thread_title)) {
        tc_send_packet_error(client, ERR_ALREADY_EXIST);
        return false;
    }
    return true;
}

static void send_new_thread(teams_server_t *server, teams_client_t *client,
    const struct cli_pck_create_thread *packet, const chat_t *thread_infos)
{
    SERVER_EVENT_THREAD_CREATED(packet->chan_uuid, thread_infos->uuid,
        thread_infos->creator, thread_infos->name, thread_infos->desc);
    tc_send_packet_info_thread(client, thread_infos);
    ts_send_event_new_thread(server, packet->team_uuid, thread_infos);
}

ns_status_e callback_create_thread(teams_server_t *server,
    teams_client_t *client, const struct cli_pck_create_thread *packet)
{
    chat_t thread_infos = { 0 };

    if (!db_is_sub_to_team(server->database, client->uuid, packet->team_uuid)) {
        tc_send_packet_error(client, ERR_NO_PERM);
        return NS_OK;
    }
    if (!can_create_thread(server, client, packet))
        return NS_OK;
    exctract_name_from_packet(thread_infos.name, packet->thread_title);
    exctract_desc_from_packet(thread_infos.desc, packet->thread_message);
    copy_uuid(thread_infos.creator, client->uuid);
    if (!db_add_thread(server->database, packet->team_uuid, packet->chan_uuid,
            &thread_infos)) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return NS_OK;
    }
    send_new_thread(server, client, packet, &thread_infos);
    return NS_OK;
}
