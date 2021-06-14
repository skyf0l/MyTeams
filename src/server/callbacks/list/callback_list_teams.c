/*
** EPITECH PROJECT, 2021
** CALLBACK_LIST_TEAMS
** File description:
** Callback list_teams
*/

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

static void send_team(teams_client_t *client, json_it_t *team_it)
{
    chat_t team_infos;

    if (!db_fill_chat_from_it(team_it, &team_infos)) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return;
    }
    tc_send_packet_info_team(client, &team_infos);
}

ns_status_e callback_list_teams(teams_server_t *server, teams_client_t *client,
    const struct cli_pck_list_teams *packet)
{
    json_object_t *teams = json_object_get_object(server->database, "teams");

    UNUSED(packet);
    if (!teams) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return NS_OK;
    }
    tc_send_packet_list_header(
        client, teams->elements_count, SERV_ID_INFO_TEAM);
    JSON_OBJECT_ITERATE(it, teams)
    {
        send_team(client, it);
    }
    return NS_OK;
}
