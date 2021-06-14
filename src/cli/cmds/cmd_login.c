/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** login_logout
*/

#include "wrapper_logging_client.h"

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

void cmd_login(teams_cli_t *cli, char *const *args)
{
    struct cli_pck_login login = {
        {
            .id = CLI_ID_LOGIN,
            .payload_length = PCK_LENGTH(struct cli_pck_login),
        },
        .username = { 0 },
    };

    CMD_CHECK_VALID_NAME(args[0]);
    if (cli->is_logged_in) {
        cli->is_logged_in = false;
        CLIENT_EVENT_LOGGED_OUT(cli->user_uuid, cli->username);
    }
    insert_name_in_packet(login.username, args[0]);
    cli_send_packet(cli, &login);
}