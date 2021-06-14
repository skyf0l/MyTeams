/*
** EPITECH PROJECT, 2021
** CALLBACK_CREATE_TEAM
** File description:
** Callback create_team
*/

#include "wrapper_logging_server.h"

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

static bool can_create_team(teams_server_t *teams_server,
    teams_client_t *teams_client, const struct cli_pck_create_team *packet)
{
    char team_name[MAX_NAME_LENGTH + 1];

    exctract_name_from_packet(team_name, packet->team_name);
    if (db_get_team_by_name(teams_server->database, team_name)) {
        tc_send_packet_error(teams_client, ERR_ALREADY_EXIST);
        return false;
    }
    return true;
}

ns_status_e callback_create_team(teams_server_t *teams_server,
    teams_client_t *teams_client, const struct cli_pck_create_team *packet)
{
    chat_t team_infos = { 0 };

    if (!can_create_team(teams_server, teams_client, packet))
        return NS_OK;
    exctract_name_from_packet(team_infos.name, packet->team_name);
    exctract_desc_from_packet(team_infos.desc, packet->team_desc);
    copy_uuid(team_infos.creator, teams_client->uuid);
    if (!db_add_team(teams_server->database, &team_infos)) {
        tc_send_packet_error(teams_client, ERR_INTERNAL);
        return NS_OK;
    }
    SERVER_EVENT_TEAM_CREATED(
        team_infos.uuid, packet->team_name, teams_client->uuid);
    tc_send_packet_info_team(teams_client, &team_infos);
    ts_send_event_new_team(teams_server, &team_infos);
    return NS_OK;
}
