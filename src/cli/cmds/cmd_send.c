/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** send_cmd
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_send(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_send send = {
        {
            .id = CLI_ID_SEND,
            .payload_length = PCK_LENGTH(struct cli_pck_send),
        },
        .user_uuid = { 0 },
        .msg = { 0 },
    };

    CMD_CHECK_VALID_UUID_STR(args[0]);
    CMD_CHECK_VALID_BODY(args[1]);
    uuid_parse(args[0], send.user_uuid);
    insert_body_in_packet(send.msg, args[1]);
    cli_send_packet(cli, &send);
}