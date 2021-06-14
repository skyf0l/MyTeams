/*
** EPITECH PROJECT, 2021
** TEAMS_CLIENT
** File description:
** Teams_client header
*/

#ifndef TEAMS_CLIENT_H_
#define TEAMS_CLIENT_H_

#include <stdbool.h>
#include <uuid/uuid.h>

#include "json/json.h"

#include "packet/prot_server.h"

#include "net/net_client.h"

// structs
typedef struct teams_server_s teams_server_t;
typedef struct message message_t;
typedef struct chat chat_t;

typedef struct teams_client_s teams_client_t;
struct teams_client_s {
    net_client_t *net_client;
    bool is_logged;
    uuid_t uuid;
    char username[MAX_NAME_LENGTH + 1];
    json_object_t *db_endpoint;
    teams_server_t *server;
};

/// PROTOTYPES

// create / destroy
teams_client_t *teams_client_create(net_client_t *net_client);
void *teams_client_destroy(teams_client_t *teams_client);

// send packets
int tc_send_packet(teams_client_t *teams_client, const void *raw_packet);

// send success / error
int tc_send_packet_success(teams_client_t *teams_client);
int tc_send_packet_error(
    teams_client_t *teams_client, enum serv_pck_error_code error_code);
int tc_send_packet_uuid_not_found(teams_client_t *teams_client,
    enum serv_pck_uuid_not_found_type type, const uuid_t uuid);

// send info
int tc_send_packet_info_user(teams_client_t *teams_client,
    const uuid_t user_uuid, const char *username, uint8_t status);
int tc_send_packet_info_msg(teams_client_t *teams_client,
    const uuid_t sender_uuid, time_t msg_timestamp, const char *msg);

int tc_send_packet_info_team(
    teams_client_t *teams_client, const chat_t *team_infos);
int tc_send_packet_info_chan(
    teams_client_t *teams_client, const chat_t *chan_infos);
int tc_send_packet_info_thread(
    teams_client_t *teams_client, const chat_t *team_infos);
int tc_send_packet_info_reply(teams_client_t *teams_client,
    const uuid_t team_uuid, const uuid_t thread_uuid, const message_t *msg);

// send list header
int tc_send_packet_list_header(teams_client_t *teams_client,
    uint16_t nb_expected_pck, uint8_t expected_serv_pck_id);

// sub
int tc_send_packet_subscription(teams_client_t *teams_client,
    const uuid_t user_uuid, const uuid_t team_uuid);
int tc_send_packet_unsubscribe(teams_client_t *teams_client,
    const uuid_t user_uuid, const uuid_t team_uuid);

// send notif
int tc_send_event(teams_client_t *teams_client, const void *raw_event);

#endif /* !TEAMS_CLIENT_H_ */