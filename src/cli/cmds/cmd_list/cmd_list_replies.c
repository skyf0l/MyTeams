/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** list_replies_cmd
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_list_replies(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_list_replies replies = {
        {
            .id = CLI_ID_LIST_REPLIES,
            .payload_length = PCK_LENGTH(struct cli_pck_list_replies),
        },
        .team_uuid = { 0 },
        .chan_uuid = { 0 },
        .thread_uuid = { 0 },
    };

    UNUSED(args);
    copy_uuid(replies.team_uuid, cli->context.team_uuid);
    copy_uuid(replies.chan_uuid, cli->context.chan_uuid);
    copy_uuid(replies.thread_uuid, cli->context.thread_uuid);
    cli_send_packet(cli, &replies);
}