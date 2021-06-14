/*
** EPITECH PROJECT, 2021
** CALLBACK_LIST_CHANS
** File description:
** Callback list_chans
*/

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

static void send_chan(teams_client_t *client, json_it_t *chan_it)
{
    chat_t chan_infos;

    if (!db_fill_chat_from_it(chan_it, &chan_infos)) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return;
    }
    tc_send_packet_info_chan(client, &chan_infos);
}

ns_status_e callback_list_chans(teams_server_t *server, teams_client_t *client,
    const struct cli_pck_list_chans *packet)
{
    json_object_t *team =
        db_get_team_by_uuid(server->database, packet->team_uuid);
    json_object_t *chans = json_object_get_object(team, "channels");

    if (!team) {
        tc_send_packet_uuid_not_found(
            client, TEAM_NOT_FOUND, packet->team_uuid);
        return NS_OK;
    }
    if (!chans) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return NS_OK;
    }
    tc_send_packet_list_header(
        client, chans->elements_count, SERV_ID_INFO_CHAN);
    JSON_OBJECT_ITERATE(it, chans)
    {
        send_chan(client, it);
    }
    return NS_OK;
}
