/*
** EPITECH PROJECT, 2021
** CMD_REPLY_SUBSCRIPTION
** File description:
** Cmd_reply_subscription function
*/

#include <stdio.h>

#include "tools.h"

#include "wrapper_logging_client.h"

#include "packet/prot_server.h"

#include "cli/teams_cli.h"

void cmd_reply_subscription(
    teams_cli_t *cli, const struct serv_pck_subscription *packet)
{
    enum cli_pck_id last_command = cli_get_last_command(cli);
    char uuid_var_str[37];
    char team_var_str[37];

    if (last_command == CLI_ID_SUB_TEAM) {
        CLIENT_PRINT_SUBSCRIBED(cli->user_uuid, packet->team_uuid);
    } else if (last_command == CLI_ID_NOTIFICATION) {
        uuid_unparse_lower(packet->user_uuid, uuid_var_str);
        uuid_unparse_lower(packet->team_uuid, team_var_str);
        printf("[Event Subscribed] %s to %s\n", uuid_var_str, team_var_str);
    } else
        printf("Receive packet subscription\n");
}