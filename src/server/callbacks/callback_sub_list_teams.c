/*
** EPITECH PROJECT, 2021
** CALLBACK_SUB_LIST_TEAMS
** File description:
** Callback sub_list_teams
*/

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

static void send_sub_list_teams(
    teams_server_t *server, teams_client_t *client, json_it_t *team_sub_it)
{
    json_object_t *team;
    chat_t team_infos;
    uuid_t team_uuid;

    if (!json_it_get_string(team_sub_it)
        || uuid_parse(json_it_get_string(team_sub_it), team_uuid) == -1) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return;
    }
    team = db_get_team_by_uuid(server->database, team_uuid);
    if (!team || !db_fill_chat(team, team_uuid, &team_infos)) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return;
    }
    tc_send_packet_info_team(client, &team_infos);
}

ns_status_e callback_sub_list_teams(teams_server_t *teams_server,
    teams_client_t *teams_client, const struct cli_pck_sub_list_teams *packet)
{
    json_array_t *teams_sub =
        json_object_get_array(teams_client->db_endpoint, "teams_sub");

    UNUSED(packet);
    if (!teams_sub) {
        tc_send_packet_error(teams_client, ERR_INTERNAL);
        return NS_OK;
    }
    tc_send_packet_list_header(
        teams_client, teams_sub->elements_count, SERV_ID_INFO_TEAM);
    JSON_ARRAY_ITERATE(it, id, teams_sub)
    {
        send_sub_list_teams(teams_server, teams_client, it);
    }
    return NS_OK;
}
