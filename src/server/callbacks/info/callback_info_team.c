/*
** EPITECH PROJECT, 2021
** CALLBACK_INFO_TEAM
** File description:
** Callback info_team
*/

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

ns_status_e callback_info_team(teams_server_t *teams_server,
    teams_client_t *teams_client, const struct cli_pck_info_team *packet)
{
    json_object_t *team;
    chat_t team_infos;

    team = db_get_team_by_uuid(teams_server->database, packet->team_uuid);
    if (!team) {
        tc_send_packet_uuid_not_found(
            teams_client, TEAM_NOT_FOUND, packet->team_uuid);
        return NS_OK;
    }
    if (!db_fill_chat(team, packet->team_uuid, &team_infos)) {
        tc_send_packet_error(teams_client, ERR_INTERNAL);
        return NS_OK;
    }
    tc_send_packet_info_team(teams_client, &team_infos);
    return NS_OK;
}
