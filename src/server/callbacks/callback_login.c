/*
** EPITECH PROJECT, 2021
** CALLBACK_LOGIN
** File description:
** Callback login
*/

#include "wrapper_logging_server.h"

#include "tools.h"

#include "packet/prot_client.h"

#include "server/database.h"
#include "server/server_callbacks.h"
#include "server/teams_server.h"

static bool user_login(teams_server_t *server, teams_client_t *client)
{
    client->db_endpoint =
        db_get_user_by_name(server->database, client->username, client->uuid);
    if (!client->db_endpoint)
        return false;
    return true;
}

static bool user_create(teams_server_t *server, teams_client_t *client)
{
    client->db_endpoint =
        db_add_user(server->database, client->uuid, client->username);
    if (!client->db_endpoint)
        return false;
    SERVER_EVENT_USER_CREATED(client->uuid, client->username);
    return true;
}

static bool update_login_status(teams_client_t *client)
{
    int login_count = 0;

    if (json_object_get_type(client->db_endpoint, "status") == j_number)
        login_count = json_object_get_int(client->db_endpoint, "status");
    return !json_object_put_int(client->db_endpoint, "status", login_count + 1);
}

ns_status_e callback_login(teams_server_t *server, teams_client_t *client,
    const struct cli_pck_login *packet)
{
    if (client->is_logged)
        callback_disconnect(server, client, NULL);
    exctract_name_from_packet(client->username, packet->username);
    if (strlen(client->username) == 0) {
        tc_send_packet_error(client, ERR_EMPTY_FIELD);
        return NS_OK;
    }
    if ((!(user_login(server, client) || user_create(server, client)))
        || !update_login_status(client)) {
        tc_send_packet_error(client, ERR_INTERNAL);
        return NS_OK;
    }
    client->is_logged = true;
    SERVER_EVENT_USER_LOGGED_IN(client->uuid);
    tc_send_packet_info_user(client, client->uuid, client->username, 1);
    ts_send_event_user(server, client, 1);
    server->nb_clients_connected++;
    return NS_OK;
}
