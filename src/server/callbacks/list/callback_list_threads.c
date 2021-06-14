/*
** EPITECH PROJECT, 2021
** CALLBACK_LIST_THREADS
** File description:
** Callback list_threads
*/

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

static void send_thread(teams_client_t *client, json_it_t *thread_it)
{
    chat_t thread_infos;

    if (!db_fill_chat_from_it(thread_it, &thread_infos)) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return;
    }
    tc_send_packet_info_thread(client, &thread_infos);
}

static json_object_t *found_threads(json_object_t *database,
    teams_client_t *client, const struct cli_pck_list_threads *packet)
{
    json_object_t *threads = db_get_team_by_uuid(database, packet->team_uuid);

    if (!threads) {
        tc_send_packet_uuid_not_found(
            client, TEAM_NOT_FOUND, packet->team_uuid);
        return NULL;
    }
    threads = db_get_channel_by_uuid(threads, packet->chan_uuid);
    if (!threads) {
        tc_send_packet_uuid_not_found(
            client, CHAN_NOT_FOUND, packet->chan_uuid);
        return NULL;
    }
    threads = json_object_get_object(threads, "threads");
    if (!threads) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return NULL;
    }
    return threads;
}

ns_status_e callback_list_threads(teams_server_t *server,
    teams_client_t *client, const struct cli_pck_list_threads *packet)
{
    json_object_t *threads = found_threads(server->database, client, packet);

    if (!threads)
        return NS_OK;
    tc_send_packet_list_header(
        client, threads->elements_count, SERV_ID_INFO_THREAD);
    JSON_OBJECT_ITERATE(it, threads)
    {
        send_thread(client, it);
    }
    return NS_OK;
}
