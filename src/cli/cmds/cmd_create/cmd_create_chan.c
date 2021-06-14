/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** create_chan_cmd
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_create_chan(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_create_chan chan = {
        {
            .id = CLI_ID_CREATE_CHAN,
            .payload_length = PCK_LENGTH(struct cli_pck_create_chan),
        },
        .team_uuid = { 0 },
        .chan_name = { 0 },
        .chan_description = { 0 },
    };

    CMD_CHECK_VALID_NAME(args[0]);
    copy_uuid(chan.team_uuid, cli->context.team_uuid);
    insert_name_in_packet(chan.chan_name, args[0]);
    if (str2d_len(args) == 2) {
        CMD_CHECK_VALID_DESC(args[1]);
        insert_desc_in_packet(chan.chan_description, args[1]);
    }
    cli_send_packet(cli, &chan);
}