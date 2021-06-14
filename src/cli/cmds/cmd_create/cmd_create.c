/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** create_cmd
*/

#include "cli/cli_cmds.h"

void cmd_create(teams_cli_t *cli, char *const *args)
{
    if (cli->context.context == NONE_CTX)
        cmd_create_team(cli, args);
    if (cli->context.context == TEAM_CTX)
        cmd_create_chan(cli, args);
    if (cli->context.context == CHAN_CTX)
        cmd_create_thread(cli, args);
    if (cli->context.context == THREAD_CTX) {
        if (str2d_len(args) != 1) {
            print_cmd_error("Invalid argument count");
            return;
        }
        cmd_create_reply(cli, args);
    }
}