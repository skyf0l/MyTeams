/*
** EPITECH PROJECT, 2021
** TC_SEND_PACKET_INFO_REPLY
** File description:
** Tc_send_packet_info_reply function
*/

#include "tools.h"

#include "server/database.h"
#include "server/teams_client.h"

int tc_send_packet_info_reply(teams_client_t *teams_client,
    const uuid_t team_uuid, const uuid_t thread_uuid, const message_t *msg)
{
    struct serv_pck_info_reply packet = {
        {
            .id = SERV_ID_INFO_REPLY,
            .payload_length = PCK_LENGTH(struct serv_pck_info_reply),
        },
        .team_uuid = { 0 },
        .thread_uuid = { 0 },
        .sender_uuid = { 0 },
        .reply_timestamp = msg->timestamp,
        .reply_msg = { 0 },
    };

    copy_uuid(packet.team_uuid, team_uuid);
    copy_uuid(packet.thread_uuid, thread_uuid);
    copy_uuid(packet.sender_uuid, msg->from);
    insert_body_in_packet(packet.reply_msg, msg->message);
    return tc_send_packet(teams_client, &packet);
}