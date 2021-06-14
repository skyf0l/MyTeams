/*
** EPITECH PROJECT, 2021
** tc_send_packet
** File description:
** tc_send_packet function
*/

#include "server/teams_client.h"

int tc_send_packet(teams_client_t *teams_client, const void *raw_packet)
{
    const struct pck *packet = (const struct pck *) raw_packet;

    return nc_send_raw(teams_client->net_client, packet,
        packet->payload_length + sizeof(struct pck));
}