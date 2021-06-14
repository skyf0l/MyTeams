/*
** EPITECH PROJECT, 2021
** SEND_EVENT
** File description:
** Send_event function
*/

#include "server/teams_client.h"

int tc_send_event(teams_client_t *teams_client, const void *raw_packet)
{
    struct serv_pck_notification notif = {
        {
            .id = SERV_ID_NOTIFICATION,
            .payload_length = PCK_LENGTH(struct serv_pck_notification),
        },
        .expected_serv_pck_id = ((const struct pck *) raw_packet)->id,
    };

    return tc_send_packet(teams_client, &notif)
        + tc_send_packet(teams_client, raw_packet);
}