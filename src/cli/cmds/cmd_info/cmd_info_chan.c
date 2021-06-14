/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** cmd_info_chan
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_info_chan(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_info_chan info_chan = {
        {
            .id = CLI_ID_INFO_CHAN,
            .payload_length = PCK_LENGTH(struct cli_pck_info_chan),
        },
        .team_uuid = { 0 },
        .chan_uuid = { 0 },
    };

    UNUSED(args);
    copy_uuid(info_chan.team_uuid, cli->context.team_uuid);
    copy_uuid(info_chan.chan_uuid, cli->context.chan_uuid);
    cli_send_packet(cli, &info_chan);
}