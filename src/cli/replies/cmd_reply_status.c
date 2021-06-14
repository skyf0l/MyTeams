/*
** EPITECH PROJECT, 2021
** CMD_REPLY_STATUS
** File description:
** Cmd_reply_status function
*/

#include <stdio.h>

#include "tools.h"

#include "packet/prot_server.h"

#include "cli/teams_cli.h"

void cmd_reply_status(teams_cli_t *cli, const struct serv_pck_status *packet)
{
    enum cli_pck_id last_command = cli_get_last_command(cli);
    char version[64 + 1];
    char motd[1024 + 1];

    UNUSED(last_command);
    exctract_string_from_packet(version, packet->version, 64);
    exctract_string_from_packet(motd, packet->motd, 1024);
    printf("Server status:\n");
    printf("\tVersion: %s\n", version);
    printf("\tMOTD: %s\n", motd);
    printf("\tUp since: %lu day(s) %02lu:%02lu:%02lu\n",
        packet->uptime / 216000, packet->uptime / 3600 % 60,
        packet->uptime / 60 % 60, packet->uptime % 60);
    printf("\tClients connected: %d/%d\n", (int) packet->clients_connected,
        (int) packet->max_clients);
}