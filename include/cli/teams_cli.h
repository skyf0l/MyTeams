/*
** EPITECH PROJECT, 2021
** TEAMS_CLI
** File description:
** Teams_cli header
*/

#ifndef TEAMS_CLI_H_
#define TEAMS_CLI_H_

#include <stdbool.h>
#include <sys/select.h>
#include <uuid/uuid.h>

#include "list/list.h"
#include "net/net_buffer.h"
#include "net/net_client.h"

#include "teams.h"

#include "packet/prot_client.h"
#include "packet/prot_server.h"

#define STD_IN (0)

// structs
typedef struct teams_cli_s teams_cli_t;

typedef struct buffered_io_s buffered_io_t;
typedef struct context_s context_t;

enum context {
    NONE_CTX,
    TEAM_CTX,
    CHAN_CTX,
    THREAD_CTX,
};

struct buffered_io_s {
    net_buffer_t write_buffer;
    fd_set need_read_fds;
    fd_set need_write_fds;
};

struct context_s {
    enum context context;
    uuid_t team_uuid;
    uuid_t chan_uuid;
    uuid_t thread_uuid;
};

struct teams_cli_s {
    bool running;
    int socket;
    buffered_io_t io;
    list_t *last_commands;
    bool is_logged_in;
    uuid_t user_uuid;
    name_t username;
    context_t context;
};

/// PROTOTYPES

// teams_cli
teams_cli_t *teams_cli_create(const char *ip, uint16_t port);
void *teams_cli_destroy(teams_cli_t *teams_cli);

int run_teams_cli(const char *ip, uint16_t port);

// main loop
void cli_loop(teams_cli_t *cli);

char **parse_cmd(const char *line);
int print_cmd_error(const char *msg);

enum cli_pck_id cli_get_last_command(teams_cli_t *cli);
void process_cmd(teams_cli_t *cli, const char *line);
void process_reply(teams_cli_t *cli, const struct pck *packet);

// write
int cli_send_packet(teams_cli_t *cli, const void *raw_packet);
int cli_flush_socket(teams_cli_t *cli);

#endif /* !TEAMS_CLI_H_ */