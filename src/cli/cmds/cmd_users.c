/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** users
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_users(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_users users = {
        {
            .id = CLI_ID_USERS,
            .payload_length = PCK_LENGTH(struct cli_pck_users),
        },
    };

    UNUSED(args);
    cli_send_packet(cli, &users);
}