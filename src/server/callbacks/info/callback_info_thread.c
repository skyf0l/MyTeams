/*
** EPITECH PROJECT, 2021
** CALLBACK_INFO_THREAD
** File description:
** Callback info_thread
*/

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

static json_object_t *fount_thread(json_object_t *database,
    teams_client_t *client, const struct cli_pck_info_thread *packet)
{
    json_object_t *thread = db_get_team_by_uuid(database, packet->team_uuid);

    if (!thread) {
        tc_send_packet_uuid_not_found(
            client, TEAM_NOT_FOUND, packet->team_uuid);
        return NULL;
    }
    thread = db_get_channel_by_uuid(thread, packet->chan_uuid);
    if (!thread) {
        tc_send_packet_uuid_not_found(
            client, CHAN_NOT_FOUND, packet->chan_uuid);
        return NULL;
    }
    thread = db_get_thread_by_uuid(thread, packet->thread_uuid);
    if (!thread) {
        tc_send_packet_uuid_not_found(
            client, THREAD_NOT_FOUND, packet->thread_uuid);
        return NULL;
    }
    return thread;
}

ns_status_e callback_info_thread(teams_server_t *server, teams_client_t *client,
    const struct cli_pck_info_thread *packet)
{
    json_object_t *thread = fount_thread(server->database, client, packet);
    chat_t thread_infos;

    if (!thread)
        return NS_OK;
    if (!db_fill_chat(thread, packet->chan_uuid, &thread_infos))
        tc_send_packet_error(client, ERR_INTERNAL);
    else
        tc_send_packet_info_thread(client, &thread_infos);
    return NS_OK;
}
