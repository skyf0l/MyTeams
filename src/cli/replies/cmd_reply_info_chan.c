/*
** EPITECH PROJECT, 2021
** CMD_REPLY_INFO_CHAN
** File description:
** Cmd_reply_info_chan function
*/

#include <stdio.h>

#include "tools.h"

#include "wrapper_logging_client.h"

#include "packet/prot_server.h"

#include "cli/teams_cli.h"

static void cmd_reply_of_notification(const struct serv_pck_info_chan *packet)
{
    CLIENT_EVENT_CHANNEL_CREATED(
        packet->chan_uuid, packet->chan_name, packet->chan_desc);
}

static void cmd_reply_of_info(const struct serv_pck_info_chan *packet)
{
    CLIENT_PRINT_CHANNEL(
        packet->chan_uuid, packet->chan_name, packet->chan_desc);
}

static void cmd_reply_of_create(const struct serv_pck_info_chan *packet)
{
    CLIENT_PRINT_CHANNEL_CREATED(
        packet->chan_uuid, packet->chan_name, packet->chan_desc);
}

static void cmd_reply_of_list(const struct serv_pck_info_chan *packet)
{
    CLIENT_TEAM_PRINT_CHANNELS(
        packet->chan_uuid, packet->chan_name, packet->chan_desc);
}

void cmd_reply_info_chan(
    teams_cli_t *cli, const struct serv_pck_info_chan *packet)
{
    enum cli_pck_id last_command = cli_get_last_command(cli);

    switch (last_command) {
    case CLI_ID_NOTIFICATION:
        cmd_reply_of_notification(packet);
        break;
    case CLI_ID_INFO_CHAN:
        cmd_reply_of_info(packet);
        break;
    case CLI_ID_CREATE_CHAN:
        cmd_reply_of_create(packet);
        break;
    case CLI_ID_LIST_CHANS:
        cmd_reply_of_list(packet);
        break;
    default:
        printf("Receive packet info_chan\n");
    }
}