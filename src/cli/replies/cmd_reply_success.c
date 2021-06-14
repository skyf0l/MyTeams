/*
** EPITECH PROJECT, 2021
** CMD_REPLY_SUCCESS
** File description:
** Cmd_reply_success function
*/

#include <stdio.h>

#include "tools.h"

#include "wrapper_logging_client.h"

#include "packet/prot_server.h"

#include "cli/teams_cli.h"

static void cmd_reply_of_logout(
    teams_cli_t *cli, const struct serv_pck_success *packet)
{
    UNUSED(packet);
    CLIENT_EVENT_LOGGED_OUT(cli->user_uuid, cli->username);
}

void cmd_reply_success(teams_cli_t *cli, const struct serv_pck_success *packet)
{
    enum cli_pck_id last_command = cli_get_last_command(cli);

    if (last_command == CLI_ID_DISCONNECT)
        cmd_reply_of_logout(cli, packet);
    else
        printf("Success\n");
}