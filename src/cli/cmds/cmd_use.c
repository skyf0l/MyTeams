/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** use_cmd
*/

#include "wrapper_logging_client.h"

#include "cli/cli_cmds.h"

static void cmd_use_team_context(teams_cli_t *cli, char *const *args)
{
    CMD_CHECK_VALID_UUID_STR(args[0]);
    cli->context.context = TEAM_CTX;
    uuid_parse(args[0], cli->context.team_uuid);
}

static void cmd_use_chan_context(teams_cli_t *cli, char *const *args)
{
    CMD_CHECK_VALID_UUID_STR(args[0]);
    CMD_CHECK_VALID_UUID_STR(args[1]);
    cli->context.context = CHAN_CTX;
    uuid_parse(args[0], cli->context.team_uuid);
    uuid_parse(args[1], cli->context.chan_uuid);
}

static void cmd_use_thread_context(teams_cli_t *cli, char *const *args)
{
    CMD_CHECK_VALID_UUID_STR(args[0]);
    CMD_CHECK_VALID_UUID_STR(args[1]);
    CMD_CHECK_VALID_UUID_STR(args[2]);
    cli->context.context = THREAD_CTX;
    uuid_parse(args[0], cli->context.team_uuid);
    uuid_parse(args[1], cli->context.chan_uuid);
    uuid_parse(args[2], cli->context.thread_uuid);
}

void cmd_use(teams_cli_t *cli, char *const *args)
{
    if (!*cli->username) {
        CLIENT_ERROR_UNAUTHORIZED();
        return;
    }
    if (str2d_len(args) == 0)
        cli->context.context = NONE_CTX;
    if (str2d_len(args) == 1)
        cmd_use_team_context(cli, args);
    if (str2d_len(args) == 2)
        cmd_use_chan_context(cli, args);
    if (str2d_len(args) == 3)
        cmd_use_thread_context(cli, args);
}