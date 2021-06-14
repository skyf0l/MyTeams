/*
** EPITECH PROJECT, 2021
** CMD_REPLY_ERROR
** File description:
** Cmd_reply_error function
*/

#include <stdio.h>

#include "tools.h"

#include "wrapper_logging_client.h"

#include "packet/prot_server.h"

#include "cli/teams_cli.h"

static void cmd_reply_of_create(enum cli_pck_id last_command)
{
    switch (last_command) {
    case CLI_ID_CREATE_TEAM:
    case CLI_ID_CREATE_CHAN:
    case CLI_ID_CREATE_THREAD:
        CLIENT_ERROR_ALREADY_EXIST();
        break;
    default:
        printf("Server error: Resource already exist\n");
    }
}

void cmd_reply_error(teams_cli_t *cli, const struct serv_pck_error *packet)
{
    enum cli_pck_id last_command = cli_get_last_command(cli);

    if (packet->error_code == ERR_INTERNAL)
        printf("Server error: Internal server error\n");
    if (packet->error_code == ERR_NOT_FOUND)
        printf("Server error: Resource not found\n");
    if (packet->error_code == ERR_NO_PERM)
        CLIENT_ERROR_UNAUTHORIZED();
    if (packet->error_code == ERR_EMPTY_FIELD)
        printf("Server error: Empty field\n");
    if (packet->error_code == ERR_NOT_IMPLEMENTED)
        printf("Server error: Resource not implemented\n");
    if (packet->error_code == ERR_ALREADY_EXIST)
        cmd_reply_of_create(last_command);
}