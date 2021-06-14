/*
** EPITECH PROJECT, 2021
** SEND_PACKET_UUID_NOT_FOUND
** File description:
** Send_packet_uuid_not_found function
*/

#include "tools.h"

#include "server/teams_client.h"

int tc_send_packet_uuid_not_found(teams_client_t *teams_client,
    enum serv_pck_uuid_not_found_type type, const uuid_t uuid)
{
    struct serv_pck_uuid_not_found packet = {
        {
            .id = SERV_ID_UUID_NOT_FOUND,
            .payload_length = PCK_LENGTH(struct serv_pck_uuid_not_found),
        },
        .type = type,
        .uuid = { 0 },
    };

    copy_uuid(packet.uuid, uuid);
    return tc_send_packet(teams_client, &packet);
}