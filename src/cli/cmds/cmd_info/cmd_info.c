/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** info_cmd
*/

#include "cli/cli_cmds.h"

void cmd_info(teams_cli_t *cli, char *const *args)
{
    if (cli->context.context == NONE_CTX)
        cmd_info_usr(cli, args);
    if (cli->context.context == TEAM_CTX)
        cmd_info_team(cli, args);
    if (cli->context.context == CHAN_CTX)
        cmd_info_chan(cli, args);
    if (cli->context.context == THREAD_CTX)
        cmd_info_thread(cli, args);
}