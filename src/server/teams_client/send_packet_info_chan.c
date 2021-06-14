/*
** EPITECH PROJECT, 2021
** TC_SEND_PACKET_INFO_CHAN
** File description:
** Tc_send_packet_info_chan function
*/

#include "tools.h"

#include "server/database.h"
#include "server/teams_client.h"

int tc_send_packet_info_chan(
    teams_client_t *teams_client, const chat_t *chan_infos)
{
    struct serv_pck_info_chan packet = {
        {
            .id = SERV_ID_INFO_CHAN,
            .payload_length = PCK_LENGTH(struct serv_pck_info_chan),
        },
        .chan_uuid = { 0 },
        .chan_name = { 0 },
        .chan_desc = { 0 },
    };

    copy_uuid(packet.chan_uuid, chan_infos->uuid);
    insert_name_in_packet(packet.chan_name, chan_infos->name);
    insert_desc_in_packet(packet.chan_desc, chan_infos->desc);
    return tc_send_packet(teams_client, &packet);
}