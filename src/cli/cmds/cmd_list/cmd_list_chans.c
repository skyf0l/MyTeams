/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** list_chans_cmd
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_list_chans(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_list_chans chans = {
        {
            .id = CLI_ID_LIST_CHANS,
            .payload_length = PCK_LENGTH(struct cli_pck_list_chans),
        },
        .team_uuid = { 0 },
    };

    UNUSED(args);
    copy_uuid(chans.team_uuid, cli->context.team_uuid);
    cli_send_packet(cli, &chans);
}