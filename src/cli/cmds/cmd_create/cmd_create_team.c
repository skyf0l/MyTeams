/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** create_team_cmd
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_create_team(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_create_team team = {
        {
            .id = CLI_ID_CREATE_TEAM,
            .payload_length = PCK_LENGTH(struct cli_pck_create_team),
        },
        .team_name = { 0 },
        .team_desc = { 0 },
    };

    CMD_CHECK_VALID_NAME(args[0]);
    insert_name_in_packet(team.team_name, args[0]);
    if (str2d_len(args) == 2) {
        CMD_CHECK_VALID_DESC(args[1]);
        insert_desc_in_packet(team.team_desc, args[1]);
    }
    cli_send_packet(cli, &team);
}