/*
** EPITECH PROJECT, 2021
** CALLBACK_CREATE_CHAN
** File description:
** Callback create_chan
*/

#include "wrapper_logging_server.h"

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

static bool can_create_chan(teams_server_t *server, teams_client_t *client,
    const struct cli_pck_create_chan *packet)
{
    json_object_t *team;
    char chan_name[MAX_NAME_LENGTH];

    team = db_get_team_by_uuid(server->database, packet->team_uuid);
    if (!team) {
        tc_send_packet_uuid_not_found(
            client, TEAM_NOT_FOUND, packet->team_uuid);
        return false;
    }
    exctract_name_from_packet(chan_name, packet->chan_name);
    if (db_get_channel_by_name(team, chan_name)) {
        tc_send_packet_error(client, ERR_ALREADY_EXIST);
        return false;
    }
    return true;
}

ns_status_e callback_create_chan(teams_server_t *server, teams_client_t *client,
    const struct cli_pck_create_chan *packet)
{
    chat_t chan_infos = { 0 };

    if (!db_is_sub_to_team(server->database, client->uuid, packet->team_uuid)) {
        tc_send_packet_error(client, ERR_NO_PERM);
        return NS_OK;
    }
    if (!can_create_chan(server, client, packet))
        return NS_OK;
    exctract_name_from_packet(chan_infos.name, packet->chan_name);
    exctract_desc_from_packet(chan_infos.desc, packet->chan_description);
    copy_uuid(chan_infos.creator, client->uuid);
    if (!db_add_channel(server->database, packet->team_uuid, &chan_infos)) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return NS_OK;
    }
    SERVER_EVENT_CHANNEL_CREATED(
        packet->team_uuid, chan_infos.uuid, chan_infos.name);
    tc_send_packet_info_chan(client, &chan_infos);
    ts_send_event_new_chan(server, packet->team_uuid, &chan_infos);
    return NS_OK;
}
