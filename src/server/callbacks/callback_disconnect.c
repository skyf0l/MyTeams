/*
** EPITECH PROJECT, 2021
** CALLBACK_DISCONNECT
** File description:
** Callback disconnect
*/

#include "wrapper_logging_server.h"

#include "tools.h"

#include "packet/prot_client.h"
#include "server/teams_server.h"

static bool update_login_status(teams_client_t *client)
{
    int login_count = json_object_get_int(client->db_endpoint, "status");

    if (login_count - 1 <= 0)
        return !json_object_remove(client->db_endpoint, "status");
    return !json_object_put_int(client->db_endpoint, "status", login_count - 1);
}

ns_status_e callback_disconnect(teams_server_t *server, teams_client_t *client,
    const struct cli_pck_disconnect *packet)
{
    SERVER_EVENT_USER_LOGGED_OUT(client->uuid);
    if (packet)
        tc_send_packet_success(client);
    ts_send_event_user(server, client, 0);
    update_login_status(client);
    server->nb_clients_connected--;
    client->is_logged = false;
    return NS_DISCONNECT_CLIENT;
}
