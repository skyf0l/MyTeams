/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** status_cmd
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_status(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_ping status = {
        {
            .id = CLI_ID_PING,
            .payload_length = PCK_LENGTH(struct cli_pck_ping),
        },
    };

    UNUSED(args);
    cli_send_packet(cli, &status);
}