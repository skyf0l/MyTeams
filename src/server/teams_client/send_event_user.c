/*
** EPITECH PROJECT, 2021
** SEND_EVENT_USER
** File description:
** Send_event_user function
*/

#include "tools.h"

#include "server/teams_client.h"
#include "server/teams_server.h"

int ts_send_event_user(
    teams_server_t *teams_server, teams_client_t *teams_client, uint8_t status)
{
    struct serv_pck_info_user packet = {
        {
            .id = SERV_ID_INFO_USER,
            .payload_length = PCK_LENGTH(struct serv_pck_info_user),
        },
        .user_uuid = { 0 },
        .username = { 0 },
        .status = status,
    };

    if (!teams_client->username)
        return -1;
    copy_uuid(packet.user_uuid, teams_client->uuid);
    insert_name_in_packet(packet.username, teams_client->username);
    return ts_send_event_to_all_other_users(
        teams_server, teams_client, &packet);
}