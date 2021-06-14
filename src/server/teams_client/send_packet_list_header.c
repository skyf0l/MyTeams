/*
** EPITECH PROJECT, 2021
** SEND_PACKET_LIST_HEADER
** File description:
** Send_packet_list_header function
*/

#include "server/teams_client.h"

int tc_send_packet_list_header(teams_client_t *teams_client,
    uint16_t nb_expected_pck, uint8_t expected_serv_pck_id)
{
    struct serv_pck_list_header packet = {
        {
            .id = SERV_ID_LIST_HEADER,
            .payload_length = PCK_LENGTH(struct serv_pck_list_header),
        },
        .nb_expected_pck = nb_expected_pck,
        .expected_serv_pck_id = expected_serv_pck_id,
    };

    return tc_send_packet(teams_client, &packet);
}