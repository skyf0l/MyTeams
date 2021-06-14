/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** message
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_messages(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_messages msg = {
        {
            .id = CLI_ID_MESSAGES,
            .payload_length = PCK_LENGTH(struct cli_pck_messages),
        },
        .user_uuid = { 0 },
    };

    UNUSED(args);
    uuid_parse(args[0], msg.user_uuid);
    cli_send_packet(cli, &msg);
}