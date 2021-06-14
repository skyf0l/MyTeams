/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** list_cmd
*/

#include "cli/cli_cmds.h"

void cmd_list(teams_cli_t *cli, char *const *args)
{
    if (cli->context.context == NONE_CTX)
        cmd_list_teams(cli, args);
    if (cli->context.context == TEAM_CTX)
        cmd_list_chans(cli, args);
    if (cli->context.context == CHAN_CTX)
        cmd_list_threads(cli, args);
    if (cli->context.context == THREAD_CTX)
        cmd_list_replies(cli, args);
}