/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** cmd_info_team
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_info_team(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_info_team info_team = {
        {
            .id = CLI_ID_INFO_TEAM,
            .payload_length = PCK_LENGTH(struct cli_pck_info_team),
        },
        .team_uuid = { 0 },
    };

    UNUSED(args);
    copy_uuid(info_team.team_uuid, cli->context.team_uuid);
    cli_send_packet(cli, &info_team);
}