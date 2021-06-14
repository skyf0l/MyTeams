/*
** EPITECH PROJECT, 2021
** TC_SEND_PACKET_INFO_THREAD
** File description:
** Tc_send_packet_info_thread function
*/

#include "tools.h"

#include "server/database.h"
#include "server/teams_client.h"

int tc_send_packet_info_thread(
    teams_client_t *teams_client, const chat_t *team_infos)
{
    struct serv_pck_info_thread packet = {
        {
            .id = SERV_ID_INFO_THREAD,
            .payload_length = PCK_LENGTH(struct serv_pck_info_thread),
        },
        .thread_uuid = { 0 },
        .user_uuid = { 0 },
        .thread_timestamp = team_infos->timestamp,
        .thread_title = { 0 },
        .thread_body = { 0 },
    };

    copy_uuid(packet.thread_uuid, team_infos->uuid);
    copy_uuid(packet.user_uuid, team_infos->creator);
    insert_name_in_packet(packet.thread_title, team_infos->name);
    insert_desc_in_packet(packet.thread_body, team_infos->desc);
    return tc_send_packet(teams_client, &packet);
}