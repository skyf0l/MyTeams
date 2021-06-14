/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** cmd_info_thread
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_info_thread(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_info_thread info_thread = {
        {
            .id = CLI_ID_INFO_THREAD,
            .payload_length = PCK_LENGTH(struct cli_pck_info_thread),
        },
        .team_uuid = { 0 },
        .chan_uuid = { 0 },
        .thread_uuid = { 0 },
    };

    UNUSED(args);
    copy_uuid(info_thread.team_uuid, cli->context.team_uuid);
    copy_uuid(info_thread.chan_uuid, cli->context.chan_uuid);
    copy_uuid(info_thread.thread_uuid, cli->context.thread_uuid);
    cli_send_packet(cli, &info_thread);
}