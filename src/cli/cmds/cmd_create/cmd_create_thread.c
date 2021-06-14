/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** create_thread_cmd
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_create_thread(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_create_thread thread = {
        {
            .id = CLI_ID_CREATE_THREAD,
            .payload_length = PCK_LENGTH(struct cli_pck_create_thread),
        },
        .team_uuid = { 0 },
        .chan_uuid = { 0 },
        .thread_title = { 0 },
        .thread_message = { 0 },
    };

    CMD_CHECK_VALID_NAME(args[0]);
    CMD_CHECK_VALID_BODY(args[1]);
    copy_uuid(thread.team_uuid, cli->context.team_uuid);
    copy_uuid(thread.chan_uuid, cli->context.chan_uuid);
    insert_name_in_packet(thread.thread_title, args[0]);
    insert_body_in_packet(thread.thread_message, args[1]);
    cli_send_packet(cli, &thread);
}