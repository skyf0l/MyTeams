/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** list_teams_cmd
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_list_teams(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_list_teams teams = {
        {
            .id = CLI_ID_LIST_TEAMS,
            .payload_length = PCK_LENGTH(struct cli_pck_list_teams),
        },
    };

    UNUSED(args);
    cli_send_packet(cli, &teams);
}