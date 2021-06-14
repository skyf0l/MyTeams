/*
** EPITECH PROJECT, 2021
** TC_SEND_PACKET_UNSUBSCRIBE
** File description:
** Tc_send_packet_unsubscribe function
*/

#include "tools.h"

#include "server/database.h"
#include "server/teams_client.h"

int tc_send_packet_unsubscribe(
    teams_client_t *client, const uuid_t user_uuid, const uuid_t team_uuid)
{
    struct serv_pck_unsubscribe packet = {
        {
            .id = SERV_ID_UNSUBSCRIBE,
            .payload_length = PCK_LENGTH(struct serv_pck_subscription),
        },
        .user_uuid = { 0 },
        .team_uuid = { 0 },
    };

    copy_uuid(packet.user_uuid, user_uuid);
    copy_uuid(packet.team_uuid, team_uuid);
    return tc_send_packet(client, &packet)
        + ts_send_event_to_sub_users(client->server, team_uuid, &packet);
}