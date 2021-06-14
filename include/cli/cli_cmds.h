/*
** EPITECH PROJECT, 2021
** CLI_CMDS
** File description:
** Cli_cmds header
*/

#ifndef CLI_CMDS_H_
#define CLI_CMDS_H_

#include <string.h>

#include "tools.h"

#include "cli/teams_cli.h"

#define ADD_CMD_PROT(name) void cmd_##name(teams_cli_t *cli, char *const *args)

// assert

#define CMD_CHECK_VALID_UUID_STR(uuid_str)                                     \
    if (!(uuid_str) || !is_valid_str_uuid(uuid_str)) {                         \
        print_cmd_error("Invalid uuid");                                       \
        return;                                                                \
    }
#define CMD_CHECK_VALID_NAME(name)                                             \
    if (!(name)) {                                                             \
        print_cmd_error("Require name");                                       \
        return;                                                                \
    }                                                                          \
    if (strlen(name) > MAX_NAME_LENGTH) {                                      \
        print_cmd_error("Name too long (max len: 32)");                        \
        return;                                                                \
    }
#define CMD_CHECK_VALID_DESC(desc)                                             \
    if (!(desc)) {                                                             \
        print_cmd_error("Require description");                                \
        return;                                                                \
    }                                                                          \
    if (strlen(desc) > MAX_DESCRIPTION_LENGTH) {                               \
        print_cmd_error("Description too long (max len: 255)");                \
        return;                                                                \
    }
#define CMD_CHECK_VALID_BODY(body)                                             \
    if (!(body)) {                                                             \
        print_cmd_error("Require body");                                       \
        return;                                                                \
    }                                                                          \
    if (!(body) || strlen(body) > MAX_BODY_LENGTH) {                           \
        print_cmd_error("Body too long (max len: 512)");                       \
        return;                                                                \
    }

struct cli_cmd {
    char const *str;
    void (*function)(teams_cli_t *, char *const *);
    size_t required_nb_args[5];
};

// sub commands
ADD_CMD_PROT(info_usr);
ADD_CMD_PROT(info_thread);
ADD_CMD_PROT(info_chan);
ADD_CMD_PROT(info_team);

ADD_CMD_PROT(create_team);
ADD_CMD_PROT(create_thread);
ADD_CMD_PROT(create_chan);
ADD_CMD_PROT(create_reply);

ADD_CMD_PROT(list_teams);
ADD_CMD_PROT(list_threads);
ADD_CMD_PROT(list_chans);
ADD_CMD_PROT(list_replies);

// help
ADD_CMD_PROT(help);

// status
ADD_CMD_PROT(status);

// login / logout
ADD_CMD_PROT(login);
ADD_CMD_PROT(logout);

// users
ADD_CMD_PROT(user);
ADD_CMD_PROT(users);

// subscription
ADD_CMD_PROT(subscribe);
ADD_CMD_PROT(subscribed);
ADD_CMD_PROT(unsubscribe);

// message
ADD_CMD_PROT(send);
ADD_CMD_PROT(messages);

// use
ADD_CMD_PROT(use);

// create
ADD_CMD_PROT(create);

// list
ADD_CMD_PROT(list);

// info
ADD_CMD_PROT(info);

static const struct cli_cmd tab[] = {
    { "/help", cmd_help, { 0, -1 } },
    { "/status", cmd_status, { 0, -1 } },
    { "/login", cmd_login, { 1, -1 } },
    { "/logout", cmd_logout, { 0, -1 } },
    { "/users", cmd_users, { 0, -1 } },
    { "/user", cmd_user, { 1, -1 } },
    { "/subscribed", cmd_subscribed, { 0, 1, -1 } },
    { "/subscribe", cmd_subscribe, { 1, -1 } },
    { "/unsubscribe", cmd_unsubscribe, { 1, -1 } },
    { "/send", cmd_send, { 2, -1 } },
    { "/messages", cmd_messages, { 1, -1 } },
    { "/use", cmd_use, { 0, 1, 2, 3, -1 } },
    { "/create", cmd_create, { 1, 2, -1 } },
    { "/list", cmd_list, { 0, -1 } },
    { "/info", cmd_info, { 0, -1 } },
    { NULL, NULL, { -1 } },
};

#endif /* !CLI_CMDS_H_ */