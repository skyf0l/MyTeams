/*
** EPITECH PROJECT, 2021
** SERVER_CORE
** File description:
** Server_core header
*/

#ifndef SERVER_CORE_H_
#define SERVER_CORE_H_

#include "net/net_client.h"
#include "net/net_server.h"

#include "packet/prot_client.h"
#include "server/teams_client.h"
#include "server/teams_server.h"

/// PROTOTYPES

int run_teams_server(int port);

/// CALLBACKS

// net callbacks
ns_status_e on_accept(net_server_t *net_server, net_client_t *net_client);
ns_status_e on_ready(net_server_t *net_server, net_client_t *net_client);
ns_status_e on_disconnect(net_server_t *net_server, net_client_t *net_client);
void on_close(net_server_t *net_server, net_client_t *net_client);

static const ns_callbacks_t net_server_callbacks = {
    .on_accept = on_accept,
    .on_ready = on_ready,
    .on_disconnect = on_disconnect,
    .on_close = on_close,
};

// teams callbacks
ns_status_e on_client_connect(
    teams_server_t *teams_server, teams_client_t *teams_client);
ns_status_e on_client_recv_packet(teams_server_t *teams_server,
    teams_client_t *teams_client, const struct pck *packet);
ns_status_e on_client_disconnect(
    teams_server_t *teams_server, teams_client_t *teams_client);
void on_client_close(
    teams_server_t *teams_server, teams_client_t *teams_client);

#endif /* !SERVER_CORE_H_ */