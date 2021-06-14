/*
** EPITECH PROJECT, 2021
** SEND_EVENT_NEW_THREAD
** File description:
** Send_event_new_tread function
*/

#include "tools.h"

#include "server/database.h"
#include "server/teams_client.h"
#include "server/teams_server.h"

int ts_send_event_new_thread(
    teams_server_t *teams_server, const uuid_t team_uuid, const chat_t *chat)
{
    struct serv_pck_info_thread packet = {
        {
            .id = SERV_ID_INFO_THREAD,
            .payload_length = PCK_LENGTH(struct serv_pck_info_thread),
        },
        .thread_uuid = { 0 },
        .user_uuid = { 0 },
        .thread_timestamp = chat->timestamp,
        .thread_title = { 0 },
        .thread_body = { 0 },
    };

    copy_uuid(packet.thread_uuid, chat->uuid);
    copy_uuid(packet.user_uuid, chat->creator);
    insert_name_in_packet(packet.thread_title, chat->name);
    insert_desc_in_packet(packet.thread_body, chat->desc);
    return ts_send_event_to_sub_users(teams_server, team_uuid, &packet);
}