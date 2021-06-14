/*
** EPITECH PROJECT, 2021
** tc_send_packet_SUCCESS
** File description:
** tc_send_packet_success function
*/

#include "server/teams_client.h"

int tc_send_packet_success(teams_client_t *teams_client)
{
    struct serv_pck_success packet = {
        {
            .id = SERV_ID_SUCCESS,
            .payload_length = PCK_LENGTH(struct serv_pck_success),
        },
    };

    return tc_send_packet(teams_client, &packet);
}