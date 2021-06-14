/*
** EPITECH PROJECT, 2021
** PROCESS_REPLIES
** File description:
** Process_replies function
*/

#include <stdio.h>

#include "cli/cli_replies.h"

void process_reply(teams_cli_t *cli, const struct pck *packet)
{
    if (packet->id >= NB_SERVER_PACKET_IDS) {
        printf("Packet error: unknown packet id: %d\n", packet->id);
        return;
    }
    if (packet->payload_length
        < cli_cmd_replies[packet->id].required_packet_length) {
        printf("Packet error: invalid packet size: packet id %d, got %lu "
                "bytes, need %lu bytes\n",
            packet->id, packet->payload_length,
            cli_cmd_replies[packet->id].required_packet_length);
        return;
    }
    cli_cmd_replies[packet->id].cmd_reply(cli, packet);
}