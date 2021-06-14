/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** cmd_info_usr
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_info_usr(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_info_usr info_usr = {
        {
            .id = CLI_ID_INFO_USR,
            .payload_length = PCK_LENGTH(struct cli_pck_info_usr),
        },
    };

    UNUSED(args);
    cli_send_packet(cli, &info_usr);
}
