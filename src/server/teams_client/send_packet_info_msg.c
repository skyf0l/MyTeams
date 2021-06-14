/*
** EPITECH PROJECT, 2021
** TC_SEND_PACKET_INFO_MSG
** File description:
** Tc_send_packet_info_msg function
*/

#include "tools.h"

#include "server/database.h"
#include "server/teams_client.h"

int tc_send_packet_info_msg(teams_client_t *teams_client,
    const uuid_t sender_uuid, time_t msg_timestamp, const char *msg)
{
    struct serv_pck_info_msg packet = {
        {
            .id = SERV_ID_INFO_MESSAGE,
            .payload_length = PCK_LENGTH(struct serv_pck_info_msg),
        },
        .sender_uuid = { 0 },
        .msg_timestamp = msg_timestamp,
        .msg = { 0 },
    };

    copy_uuid(packet.sender_uuid, sender_uuid);
    insert_body_in_packet(packet.msg, msg);
    return tc_send_packet(teams_client, &packet);
}