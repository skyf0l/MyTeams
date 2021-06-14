/*
** EPITECH PROJECT, 2021
** TC_SEND_PACKET_INFO_USER
** File description:
** Tc_send_packet_info_user function
*/

#include "tools.h"

#include "server/teams_client.h"

int tc_send_packet_info_user(teams_client_t *teams_client,
    const uuid_t user_uuid, const char *username, uint8_t status)
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

    if (!username)
        return tc_send_packet_error(teams_client, ERR_INTERNAL);
    copy_uuid(packet.user_uuid, user_uuid);
    insert_name_in_packet(packet.username, username);
    return tc_send_packet(teams_client, &packet);
}