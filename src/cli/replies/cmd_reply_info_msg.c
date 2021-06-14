/*
** EPITECH PROJECT, 2021
** CMD_REPLY_INFO_MSG
** File description:
** Cmd_reply_info_msg function
*/

#include <stdio.h>

#include "tools.h"

#include "wrapper_logging_client.h"

#include "packet/prot_server.h"

#include "cli/teams_cli.h"

static void cmd_reply_of_notification(const struct serv_pck_info_msg *packet)
{
    CLIENT_EVENT_PRIVATE_MESSAGE_RECEIVED(packet->sender_uuid, packet->msg);
}

static void cmd_reply_of_send(void)
{
    printf("Message sent successfully\n");
}

static void cmd_reply_of_messages(const struct serv_pck_info_msg *packet)
{
    CLIENT_PRIVATE_MESSAGE_PRINT_MESSAGES(
        packet->sender_uuid, packet->msg_timestamp, packet->msg);
}

void cmd_reply_info_msg(
    teams_cli_t *cli, const struct serv_pck_info_msg *packet)
{
    enum cli_pck_id last_command = cli_get_last_command(cli);

    switch (last_command) {
    case CLI_ID_NOTIFICATION:
        cmd_reply_of_notification(packet);
        break;
    case CLI_ID_SEND:
        cmd_reply_of_send();
        break;
    case CLI_ID_MESSAGES:
        cmd_reply_of_messages(packet);
        break;
    default:
        printf("Receive packet info_msg\n");
    }
}