/*
** EPITECH PROJECT, 2021
** TC_SEND_PACKET_INFO_TEAM
** File description:
** Tc_send_packet_info_team function
*/

#include "tools.h"

#include "server/database.h"
#include "server/teams_client.h"

int tc_send_packet_info_team(
    teams_client_t *teams_client, const chat_t *team_infos)
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

    copy_uuid(packet.team_uuid, team_infos->uuid);
    insert_name_in_packet(packet.team_name, team_infos->name);
    insert_desc_in_packet(packet.team_desc, team_infos->desc);
    return tc_send_packet(teams_client, &packet);
}