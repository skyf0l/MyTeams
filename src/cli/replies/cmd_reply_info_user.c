/*
** EPITECH PROJECT, 2021
** CMD_REPLY_INFO_USER
** File description:
** Cmd_reply_info_user function
*/

#include <stdio.h>

#include "tools.h"

#include "wrapper_logging_client.h"

#include "packet/prot_server.h"

#include "cli/teams_cli.h"

static void cmd_reply_of_notification(const struct serv_pck_info_user *packet)
{
    if (packet->status) {
        CLIENT_EVENT_LOGGED_IN(packet->user_uuid, packet->username);
    } else {
        CLIENT_EVENT_LOGGED_OUT(packet->user_uuid, packet->username);
    }
}

static void cmd_reply_of_login(
    teams_cli_t *cli, const struct serv_pck_info_user *packet)
{
    copy_uuid(cli->user_uuid, packet->user_uuid);
    exctract_name_from_packet(cli->username, packet->username);
    cli->is_logged_in = true;
    CLIENT_EVENT_LOGGED_IN(packet->user_uuid, packet->username);
}

static void cmd_reply_of_user(
    teams_cli_t *cli, const struct serv_pck_info_user *packet)
{
    UNUSED(cli);
    CLIENT_PRINT_USER(packet->user_uuid, packet->username, packet->status);
}

static void cmd_reply_of_userssubscribed(
    teams_cli_t *cli, const struct serv_pck_info_user *packet)
{
    UNUSED(cli);
    CLIENT_PRINT_USERS(packet->user_uuid, packet->username, packet->status);
}

void cmd_reply_info_user(
    teams_cli_t *cli, const struct serv_pck_info_user *packet)
{
    enum cli_pck_id last_command = cli_get_last_command(cli);

    switch (last_command) {
    case CLI_ID_NOTIFICATION:
        cmd_reply_of_notification(packet);
        break;
    case CLI_ID_LOGIN:
        cmd_reply_of_login(cli, packet);
        break;
    case CLI_ID_USER:
    case CLI_ID_INFO_USR:
        cmd_reply_of_user(cli, packet);
        break;
    case CLI_ID_SUB_USR_TEAM:
    case CLI_ID_USERS:
        cmd_reply_of_userssubscribed(cli, packet);
        break;
    default:
        printf("Receive packet info_user\n");
    }
}