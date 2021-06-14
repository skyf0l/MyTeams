/*
** EPITECH PROJECT, 2021
** CLI_CMD_REPLIES
** File description:
** Cli_cmd_replies header
*/

#ifndef CLI_CMD_REPLIES_H_
#define CLI_CMD_REPLIES_H_

#include "packet/prot_server.h"

#include "cli/teams_cli.h"

#define CMD_REPLY_PROT void (*)(teams_cli_t * cli, const struct pck *packet)

#define ADD_CMD_REPLY_PROT(name)                                               \
    void cmd_reply_##name(                                                     \
        teams_cli_t *cli, const struct serv_pck_##name *packet)

#define SERV_PCK_SIZE(name) PCK_LENGTH(struct serv_pck_##name)

struct cli_cmd_reply {
    void (*cmd_reply)(teams_cli_t *, const struct pck *);
    uint16_t required_packet_length;
};

ADD_CMD_REPLY_PROT(error);
ADD_CMD_REPLY_PROT(success);
ADD_CMD_REPLY_PROT(info_user);
ADD_CMD_REPLY_PROT(status);
ADD_CMD_REPLY_PROT(subscription);
ADD_CMD_REPLY_PROT(unsubscribe);
ADD_CMD_REPLY_PROT(info_team);
ADD_CMD_REPLY_PROT(info_chan);
ADD_CMD_REPLY_PROT(info_thread);
ADD_CMD_REPLY_PROT(info_reply);
ADD_CMD_REPLY_PROT(info_msg);
ADD_CMD_REPLY_PROT(list_header);
ADD_CMD_REPLY_PROT(set_aes_encryption);
ADD_CMD_REPLY_PROT(notification);
ADD_CMD_REPLY_PROT(uuid_not_found);

static const struct cli_cmd_reply cli_cmd_replies[] = {
    { (CMD_REPLY_PROT) cmd_reply_error, SERV_PCK_SIZE(error) },
    { (CMD_REPLY_PROT) cmd_reply_success, SERV_PCK_SIZE(success) },
    { (CMD_REPLY_PROT) cmd_reply_info_user, SERV_PCK_SIZE(info_user) },
    { (CMD_REPLY_PROT) cmd_reply_status, SERV_PCK_SIZE(status) },
    { (CMD_REPLY_PROT) cmd_reply_subscription, SERV_PCK_SIZE(subscription) },
    { (CMD_REPLY_PROT) cmd_reply_unsubscribe, SERV_PCK_SIZE(unsubscribe) },
    { (CMD_REPLY_PROT) cmd_reply_info_team, SERV_PCK_SIZE(info_team) },
    { (CMD_REPLY_PROT) cmd_reply_info_chan, SERV_PCK_SIZE(info_chan) },
    { (CMD_REPLY_PROT) cmd_reply_info_thread, SERV_PCK_SIZE(info_thread) },
    { (CMD_REPLY_PROT) cmd_reply_info_reply, SERV_PCK_SIZE(info_reply) },
    { (CMD_REPLY_PROT) cmd_reply_info_msg, SERV_PCK_SIZE(info_msg) },
    { (CMD_REPLY_PROT) cmd_reply_list_header, SERV_PCK_SIZE(list_header) },
    { (CMD_REPLY_PROT) cmd_reply_set_aes_encryption,
        SERV_PCK_SIZE(set_aes_encryption) },
    { (CMD_REPLY_PROT) cmd_reply_notification, SERV_PCK_SIZE(notification) },
    { (CMD_REPLY_PROT) cmd_reply_uuid_not_found,
        SERV_PCK_SIZE(uuid_not_found) },
};

#endif /* !CLI_CMD_REPLIES_H_ */