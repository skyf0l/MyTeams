/*
** EPITECH PROJECT, 2021
** CMD_REPLY_NOTIFICATION
** File description:
** Cmd_reply_notification function
*/

#include <stdio.h>

#include "tools.h"

#include "packet/prot_server.h"

#include "cli/teams_cli.h"

void cmd_reply_notification(
    teams_cli_t *cli, const struct serv_pck_notification *packet)
{
    UNUSED(packet);
    list_add_at(
        cli->last_commands, (void *) (uintptr_t) CLI_ID_NOTIFICATION, 0);
}