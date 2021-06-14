/*
** EPITECH PROJECT, 2021
** CALLBACK_INFO_USR
** File description:
** Callback info_usr
*/

#include "tools.h"

#include "packet/prot_client.h"
#include "server/teams_server.h"

ns_status_e callback_info_usr(teams_server_t *teams_server,
    teams_client_t *teams_client, const struct cli_pck_info_usr *packet)
{
    UNUSED(teams_server), UNUSED(packet);
    tc_send_packet_info_user(
        teams_client, teams_client->uuid, teams_client->username, 1);
    return NS_OK;
}
