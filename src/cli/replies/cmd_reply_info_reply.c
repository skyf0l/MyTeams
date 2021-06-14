/*
** EPITECH PROJECT, 2021
** CMD_REPLY_INFO_REPLY
** File description:
** Cmd_reply_info_reply function
*/

#include <stdio.h>

#include "tools.h"

#include "wrapper_logging_client.h"

#include "wrapper_logging_client.h"

#include "packet/prot_server.h"

#include "cli/teams_cli.h"

static void cmd_reply_of_notification(const struct serv_pck_info_reply *packet)
{
    CLIENT_EVENT_THREAD_REPLY_RECEIVED(packet->team_uuid, packet->thread_uuid,
        packet->sender_uuid, packet->reply_msg);
}

static void cmd_reply_of_create(const struct serv_pck_info_reply *packet)
{
    CLIENT_PRINT_REPLY_CREATED(packet->thread_uuid, packet->sender_uuid,
        packet->reply_timestamp, packet->reply_msg);
}

static void cmd_reply_of_list(const struct serv_pck_info_reply *packet)
{
    CLIENT_THREAD_PRINT_REPLIES(packet->thread_uuid, packet->sender_uuid,
        packet->reply_timestamp, packet->reply_msg);
}

void cmd_reply_info_reply(
    teams_cli_t *cli, const struct serv_pck_info_reply *packet)
{
    enum cli_pck_id last_command = cli_get_last_command(cli);

    switch (last_command) {
    case CLI_ID_NOTIFICATION:
        cmd_reply_of_notification(packet);
        break;
    case CLI_ID_CREATE_REPLY:
        cmd_reply_of_create(packet);
        break;
    case CLI_ID_LIST_REPLIES:
        cmd_reply_of_list(packet);
        break;
    default:
        printf("Receive packet info_reply\n");
    }
}