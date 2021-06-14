/*
** EPITECH PROJECT, 2021
** CMD_REPLY_INFO_TEAM
** File description:
** Cmd_reply_info_team function
*/

#include <stdio.h>

#include "tools.h"

#include "wrapper_logging_client.h"

#include "packet/prot_server.h"

#include "cli/teams_cli.h"

static void cmd_reply_of_notification(const struct serv_pck_info_team *packet)
{
    CLIENT_EVENT_TEAM_CREATED(
        packet->team_uuid, packet->team_name, packet->team_desc);
}

static void cmd_reply_of_info(const struct serv_pck_info_team *packet)
{
    CLIENT_PRINT_TEAM(packet->team_uuid, packet->team_name, packet->team_desc);
}

static void cmd_reply_of_create(const struct serv_pck_info_team *packet)
{
    CLIENT_PRINT_TEAM_CREATED(
        packet->team_uuid, packet->team_name, packet->team_desc);
}

static void cmd_reply_of_list_subscribed(
    const struct serv_pck_info_team *packet)
{
    CLIENT_PRINT_TEAMS(packet->team_uuid, packet->team_name, packet->team_desc);
}

void cmd_reply_info_team(
    teams_cli_t *cli, const struct serv_pck_info_team *packet)
{
    enum cli_pck_id last_command = cli_get_last_command(cli);

    switch (last_command) {
    case CLI_ID_NOTIFICATION:
        cmd_reply_of_notification(packet);
        break;
    case CLI_ID_INFO_TEAM:
        cmd_reply_of_info(packet);
        break;
    case CLI_ID_CREATE_TEAM:
        cmd_reply_of_create(packet);
        break;
    case CLI_ID_LIST_TEAMS:
    case CLI_ID_SUB_LIST_TEAMS:
        cmd_reply_of_list_subscribed(packet);
        break;
    default:
        printf("Receive packet info_team\n");
    }
}