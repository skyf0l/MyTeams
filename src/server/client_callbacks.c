/*
** EPITECH PROJECT, 2021
** CLIENT_CALLBACKS
** File description:
** Client_callbacks function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tools.h"

#include "server/server_callbacks.h"
#include "server/teams_client.h"
#include "server/teams_server.h"

ns_status_e on_client_connect(
    teams_server_t *teams_server, teams_client_t *teams_client)
{
    UNUSED(teams_server), UNUSED(teams_client);
    printf("Client connect\n");
    return NS_OK;
}

ns_status_e on_client_recv_packet(teams_server_t *teams_server,
    teams_client_t *teams_client, const struct pck *pck)
{
    if (pck->id >= NB_CLIENT_PACKET_IDS) {
        tc_send_packet_error(teams_client, ERR_NOT_IMPLEMENTED);
        printf("Packet error: unknown packet id %d\n", pck->id);
        return NS_OK;
    }
    if (pck->payload_length
        < server_callbacks[pck->id].required_packet_length) {
        tc_send_packet_error(teams_client, ERR_INTERNAL);
        printf("Packet error: invalid packet size: packet id %d, got %lu "
                "bytes, need %lu bytes\n",
            pck->id, pck->payload_length,
            server_callbacks[pck->id].required_packet_length);
        return NS_OK;
    }
    if (server_callbacks[pck->id].need_logged_in && !teams_client->is_logged) {
        tc_send_packet_error(teams_client, ERR_NO_PERM);
        printf("Packet error: user is not logged in\n");
        return NS_OK;
    }
    return server_callbacks[pck->id].callback(teams_server, teams_client, pck);
}

ns_status_e on_client_disconnect(
    teams_server_t *teams_server, teams_client_t *teams_client)
{
    if (teams_client->is_logged)
        callback_disconnect(teams_server, teams_client, NULL);
    printf("Client disconnected\n");
    return NS_OK;
}

ns_status_e on_client_close(
    teams_server_t *teams_server, teams_client_t *teams_client)
{
    UNUSED(teams_server), UNUSED(teams_client);
    printf("Client closed\n");
    return NS_OK;
}