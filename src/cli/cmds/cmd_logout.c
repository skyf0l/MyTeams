/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** logout_cmd
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_logout(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_disconnect logout = {
        {
            .id = CLI_ID_DISCONNECT,
            .payload_length = PCK_LENGTH(struct cli_pck_disconnect),
        },
    };

    UNUSED(args);
    cli->is_logged_in = false;
    cli_send_packet(cli, &logout);
}