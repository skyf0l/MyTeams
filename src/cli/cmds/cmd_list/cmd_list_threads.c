/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** list_threads
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_list_threads(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_list_threads threads = {
        {
            .id = CLI_ID_LIST_THREADS,
            .payload_length = PCK_LENGTH(struct cli_pck_list_threads),
        },
        .team_uuid = { 0 },
        .chan_uuid = { 0 },
    };

    UNUSED(args);
    copy_uuid(threads.team_uuid, cli->context.team_uuid);
    copy_uuid(threads.chan_uuid, cli->context.chan_uuid);
    cli_send_packet(cli, &threads);
}