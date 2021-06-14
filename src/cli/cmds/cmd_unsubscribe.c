/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** unsubscribe_cmd
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_unsubscribe(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_unsub_team unsub = {
        {
            .id = CLI_ID_UNSUB_TEAM,
            .payload_length = PCK_LENGTH(struct cli_pck_unsub_team),
        },
        .team_uuid = { 0 },
    };

    CMD_CHECK_VALID_UUID_STR(args[0]);
    uuid_parse(args[0], unsub.team_uuid);
    cli_send_packet(cli, &unsub);
}