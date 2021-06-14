/*
** EPITECH PROJECT, 2021
** TEAMS_SERVER
** File description:
** Teams_server header
*/

#ifndef TEAMS_SERVER_H_
#define TEAMS_SERVER_H_

#include "net/net_client.h"
#include "net/net_server.h"
#include "json/json.h"

#include "server/teams_client.h"

typedef struct message message_t;
typedef struct chat chat_t;

typedef struct teams_server_s teams_server_t;
struct teams_server_s {
    net_server_t *net_server;
    json_object_t *database;
    uint64_t nb_clients_connected;
    uint64_t start_time;
};

/// PROTOTYPES

// create / destroy
teams_server_t *teams_server_create(net_server_t *net_server);
void *teams_server_destroy(teams_server_t *teams_server);

// send events
int ts_send_event_to_user(teams_server_t *teams_server, const uuid_t user_uuid,
    const void *raw_event);
int ts_send_event_to_all_other_users(teams_server_t *teams_server,
    teams_client_t *teams_client, const void *raw_event);
int ts_send_event_to_all_users(
    teams_server_t *teams_server, const void *raw_event);
int ts_send_event_to_sub_users(teams_server_t *teams_server,
    const uuid_t team_uuid, const void *raw_event);

// events
int ts_send_event_user(
    teams_server_t *teams_server, teams_client_t *teams_client, uint8_t status);
int ts_send_event_new_msg(teams_server_t *teams_server, const message_t *pm);

int ts_send_event_new_team(teams_server_t *teams_server, const chat_t *chat);
int ts_send_event_new_chan(
    teams_server_t *teams_server, const uuid_t team_uuid, const chat_t *chat);
int ts_send_event_new_thread(
    teams_server_t *teams_server, const uuid_t team_uuid, const chat_t *chat);
int ts_send_event_new_reply(teams_server_t *teams_server,
    const uuid_t team_uuid, const uuid_t thread_uuid, const message_t *msg);
#endif /* !TEAMS_SERVER_H_ */