/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** user_cmd
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_user(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_user user = {
        {
            .id = CLI_ID_USER,
            .payload_length = PCK_LENGTH(struct cli_pck_user),
        },
        .user_uuid = { 0 },
    };

    CMD_CHECK_VALID_UUID_STR(args[0]);
    uuid_parse(args[0], user.user_uuid);
    cli_send_packet(cli, &user);
}