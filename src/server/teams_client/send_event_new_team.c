/*
** EPITECH PROJECT, 2021
** SEND_EVENT_NEW_TEAM
** File description:
** Send_event_new_team function
*/

#include "tools.h"

#include "server/database.h"
#include "server/teams_client.h"
#include "server/teams_server.h"

int ts_send_event_new_team(teams_server_t *teams_server, const chat_t *chat)
{
    struct serv_pck_info_team packet = {
        {
            .id = SERV_ID_INFO_TEAM,
            .payload_length = PCK_LENGTH(struct serv_pck_info_team),
        },
        .team_uuid = { 0 },
        .team_name = { 0 },
        .team_desc = { 0 },
    };

    copy_uuid(packet.team_uuid, chat->uuid);
    insert_name_in_packet(packet.team_name, chat->name);
    insert_desc_in_packet(packet.team_desc, chat->desc);
    return ts_send_event_to_all_users(teams_server, &packet);
}