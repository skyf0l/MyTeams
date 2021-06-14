/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** create_reply_cmd
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_create_reply(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_create_reply reply = {
        {
            .id = CLI_ID_CREATE_REPLY,
            .payload_length = PCK_LENGTH(struct cli_pck_create_reply),
        },
        .team_uuid = { 0 },
        .chan_uuid = { 0 },
        .thread_uuid = { 0 },
        .reply_msg = { 0 },
    };

    CMD_CHECK_VALID_BODY(args[0]);
    copy_uuid(reply.team_uuid, cli->context.team_uuid);
    copy_uuid(reply.chan_uuid, cli->context.chan_uuid);
    copy_uuid(reply.thread_uuid, cli->context.thread_uuid);
    insert_body_in_packet(reply.reply_msg, args[0]);
    cli_send_packet(cli, &reply);
}