/*
** EPITECH PROJECT, 2021
** SEND_EVENT_NEW_MSG
** File description:
** Send_event_new_msg function
*/

#include "tools.h"

#include "server/database.h"
#include "server/teams_client.h"
#include "server/teams_server.h"

int ts_send_event_new_msg(teams_server_t *teams_server, const message_t *pm)
{
    struct serv_pck_info_msg packet = {
        {
            .id = SERV_ID_INFO_MESSAGE,
            .payload_length = PCK_LENGTH(struct serv_pck_info_msg),
        },
        .sender_uuid = { 0 },
        .msg_timestamp = pm->timestamp,
        .msg = { 0 },
    };

    copy_uuid(packet.sender_uuid, pm->from);
    insert_body_in_packet(packet.msg, pm->message);
    return ts_send_event_to_user(teams_server, pm->to, &packet);
}