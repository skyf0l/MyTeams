/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** subscription
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_subscribe(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_sub_team sub_team = {
        {
            .id = CLI_ID_SUB_TEAM,
            .payload_length = PCK_LENGTH(struct cli_pck_sub_team),
        },
        .team_uuid = { 0 },
    };

    CMD_CHECK_VALID_UUID_STR(args[0]);
    uuid_parse(args[0], sub_team.team_uuid);
    cli_send_packet(cli, &sub_team);
}