/*
** EPITECH PROJECT, 2021
** tc_send_packet_ERROR
** File description:
** tc_send_packet_error function
*/

#include "server/teams_client.h"

int tc_send_packet_error(
    teams_client_t *teams_client, enum serv_pck_error_code error_code)
{
    struct serv_pck_error packet = {
        {
            .id = SERV_ID_ERROR,
            .payload_length = PCK_LENGTH(struct serv_pck_error),
        },
        .error_code = error_code,
    };

    return tc_send_packet(teams_client, &packet);
}