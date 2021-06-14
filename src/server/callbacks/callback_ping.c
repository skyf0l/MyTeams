/*
** EPITECH PROJECT, 2021
** CALLBACK_PING
** File description:
** Callback ping
*/

#include <time.h>

#include "tools.h"

#include "packet/prot_client.h"
#include "server/teams_server.h"

ns_status_e callback_ping(teams_server_t *teams_server,
    teams_client_t *teams_client, const struct cli_pck_ping *packet)
{
    struct serv_pck_status packet_status = {
        {
            .id = SERV_ID_STATUS,
            .payload_length = PCK_LENGTH(struct serv_pck_status),
        },
        .version = { 0 },
        .uptime = time(NULL) - teams_server->start_time,
        .clients_connected = teams_server->nb_clients_connected,
        .max_clients = -1,
        .motd = { 0 },
    };

    UNUSED(packet);
    insert_string_in_packet(packet_status.version, VERSION, 64);
    insert_string_in_packet(packet_status.motd, MOTD, 1024);
    tc_send_packet(teams_client, &packet_status);
    return NS_OK;
}
