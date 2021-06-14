/*
** EPITECH PROJECT, 2021
** CMD_REPLY_INFO_THREAD
** File description:
** Cmd_reply_info_thread function
*/

#include <stdio.h>

#include "tools.h"

#include "wrapper_logging_client.h"

#include "packet/prot_server.h"

#include "cli/teams_cli.h"

static void cmd_reply_of_notification(const struct serv_pck_info_thread *packet)
{
    CLIENT_EVENT_THREAD_CREATED(packet->thread_uuid, packet->user_uuid,
        packet->thread_timestamp, packet->thread_title, packet->thread_body);
}

static void cmd_reply_of_info(const struct serv_pck_info_thread *packet)
{
    CLIENT_PRINT_THREAD(packet->thread_uuid, packet->user_uuid,
        packet->thread_timestamp, packet->thread_title, packet->thread_body);
}

static void cmd_reply_of_create(const struct serv_pck_info_thread *packet)
{
    CLIENT_PRINT_THREAD_CREATED(packet->thread_uuid, packet->user_uuid,
        packet->thread_timestamp, packet->thread_title, packet->thread_body);
}

static void cmd_reply_of_list(const struct serv_pck_info_thread *packet)
{
    CLIENT_CHANNEL_PRINT_THREADS(packet->thread_uuid, packet->user_uuid,
        packet->thread_timestamp, packet->thread_title, packet->thread_body);
}

void cmd_reply_info_thread(
    teams_cli_t *cli, const struct serv_pck_info_thread *packet)
{
    enum cli_pck_id last_command = cli_get_last_command(cli);

    switch (last_command) {
    case CLI_ID_NOTIFICATION:
        cmd_reply_of_notification(packet);
        break;
    case CLI_ID_INFO_THREAD:
        cmd_reply_of_info(packet);
        break;
    case CLI_ID_CREATE_THREAD:
        cmd_reply_of_create(packet);
        break;
    case CLI_ID_LIST_THREADS:
        cmd_reply_of_list(packet);
        break;
    default:
        printf("Receive packet info_thread\n");
    }
}