/*
** EPITECH PROJECT, 2021
** CALLBACK_SET_COMP
** File description:
** Callback set_comp
*/

#include "tools.h"

#include "packet/prot_client.h"
#include "server/teams_server.h"

ns_status_e callback_set_comp(teams_server_t *teams_server,
    teams_client_t *teams_client, const struct cli_pck_set_comp *packet)
{
    UNUSED(teams_server), UNUSED(packet);
    tc_send_packet_error(teams_client, ERR_NOT_IMPLEMENTED);
    return NS_OK;
}
