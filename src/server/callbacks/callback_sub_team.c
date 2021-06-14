/*
** EPITECH PROJECT, 2021
** CALLBACK_SUB_TEAM
** File description:
** Callback sub_team
*/

#include "wrapper_logging_server.h"

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/teams_server.h"

ns_status_e callback_sub_team(teams_server_t *teams_server,
    teams_client_t *teams_client, const struct cli_pck_sub_team *packet)
{
    if (!db_get_team_by_uuid(teams_server->database, packet->team_uuid)) {
        tc_send_packet_uuid_not_found(
            teams_client, TEAM_NOT_FOUND, packet->team_uuid);
        return NS_OK;
    }
    if (!db_subscribe_team(
            teams_server->database, teams_client->uuid, packet->team_uuid)) {
        tc_send_packet_error(teams_client, ERR_INTERNAL);
        return NS_OK;
    }
    SERVER_EVENT_USER_SUBSCRIBED(packet->team_uuid, teams_client->uuid);
    tc_send_packet_subscription(
        teams_client, teams_client->uuid, packet->team_uuid);
    return NS_OK;
}
