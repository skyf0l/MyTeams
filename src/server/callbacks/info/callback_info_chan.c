/*
** EPITECH PROJECT, 2021
** CALLBACK_INFO_CHAN
** File description:
** Callback info_chan
*/

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

ns_status_e callback_info_chan(teams_server_t *server, teams_client_t *client,
    const struct cli_pck_info_chan *packet)
{
    json_object_t *team =
        db_get_team_by_uuid(server->database, packet->team_uuid);
    json_object_t *chan = db_get_channel_by_uuid(team, packet->chan_uuid);
    chat_t chan_infos;

    if (!team) {
        tc_send_packet_uuid_not_found(
            client, TEAM_NOT_FOUND, packet->team_uuid);
        return NS_OK;
    }
    if (!chan) {
        tc_send_packet_uuid_not_found(
            client, CHAN_NOT_FOUND, packet->chan_uuid);
        return NS_OK;
    }
    if (!db_fill_chat(chan, packet->chan_uuid, &chan_infos))
        tc_send_packet_error(client, ERR_INTERNAL);
    else
        tc_send_packet_info_chan(client, &chan_infos);
    return NS_OK;
}
