/*
** EPITECH PROJECT, 2021
** SEND_EVENT_NEW_CHAN
** File description:
** Send_event_new_chan function
*/

#include "tools.h"

#include "server/database.h"
#include "server/teams_client.h"
#include "server/teams_server.h"

int ts_send_event_new_chan(
    teams_server_t *teams_server, const uuid_t team_uuid, const chat_t *chat)
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

    copy_uuid(packet.chan_uuid, chat->uuid);
    insert_name_in_packet(packet.chan_name, chat->name);
    insert_desc_in_packet(packet.chan_desc, chat->desc);
    return ts_send_event_to_sub_users(teams_server, team_uuid, &packet);
}