/*
** EPITECH PROJECT, 2021
** CMD_REPLY_UUID_NOT_FOUND
** File description:
** Cmd_reply_uuid_not_found function
*/

#include <stdio.h>

#include "tools.h"

#include "wrapper_logging_client.h"

#include "packet/prot_server.h"

#include "cli/teams_cli.h"

void cmd_reply_uuid_not_found(
    teams_cli_t *cli, const struct serv_pck_uuid_not_found *packet)
{
    enum cli_pck_id last_command = cli_get_last_command(cli);

    UNUSED(last_command);
    switch (packet->type) {
    case USER_NOT_FOUND:
        CLIENT_ERROR_UNKNOWN_USER(packet->uuid)
        break;
    case TEAM_NOT_FOUND:
        CLIENT_ERROR_UNKNOWN_TEAM(packet->uuid)
        break;
    case CHAN_NOT_FOUND:
        CLIENT_ERROR_UNKNOWN_CHANNEL(packet->uuid)
        break;
    case THREAD_NOT_FOUND:
        CLIENT_ERROR_UNKNOWN_THREAD(packet->uuid)
        break;
    }
}