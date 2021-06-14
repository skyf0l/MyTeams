/*
** EPITECH PROJECT, 2021
** SERVER_CALLBACKS
** File description:
** Server_callbacks header
*/

#ifndef SERVER_CALLBACKS_H_
#define SERVER_CALLBACKS_H_

#include "packet/prot_client.h"

#include "server/teams_server.h"

#define CALLBACK_PROT                                                          \
    ns_status_e (*)(teams_server_t *, teams_client_t *, const struct pck *)

#define ADD_CALLBACK_PROT(name)                                                \
    ns_status_e callback_##name(teams_server_t *teams_server,                  \
        teams_client_t *teams_client, const struct cli_pck_##name *packet)

#define CLI_PCK_SIZE(name) PCK_LENGTH(struct cli_pck_##name)

struct server_callback {
    ns_status_e (*callback)(
        teams_server_t *, teams_client_t *, const struct pck *);
    uint16_t required_packet_length;
    bool need_logged_in;
};

ADD_CALLBACK_PROT(login);
ADD_CALLBACK_PROT(disconnect);
ADD_CALLBACK_PROT(users);
ADD_CALLBACK_PROT(user);
ADD_CALLBACK_PROT(send);
ADD_CALLBACK_PROT(messages);
ADD_CALLBACK_PROT(sub_team);
ADD_CALLBACK_PROT(sub_usr_team);
ADD_CALLBACK_PROT(sub_list_teams);
ADD_CALLBACK_PROT(unsub_team);
ADD_CALLBACK_PROT(create_team);
ADD_CALLBACK_PROT(create_chan);
ADD_CALLBACK_PROT(create_thread);
ADD_CALLBACK_PROT(create_reply);
ADD_CALLBACK_PROT(list_teams);
ADD_CALLBACK_PROT(list_chans);
ADD_CALLBACK_PROT(list_threads);
ADD_CALLBACK_PROT(list_replies);
ADD_CALLBACK_PROT(info_usr);
ADD_CALLBACK_PROT(info_team);
ADD_CALLBACK_PROT(info_chan);
ADD_CALLBACK_PROT(info_thread);
ADD_CALLBACK_PROT(ping);
ADD_CALLBACK_PROT(set_comp);
ADD_CALLBACK_PROT(set_enc);

static const struct server_callback server_callbacks[] = {
    { (CALLBACK_PROT) callback_login, CLI_PCK_SIZE(login), false },
    { (CALLBACK_PROT) callback_disconnect, CLI_PCK_SIZE(disconnect), true },
    { (CALLBACK_PROT) callback_users, CLI_PCK_SIZE(users), true },
    { (CALLBACK_PROT) callback_user, CLI_PCK_SIZE(user), true },
    { (CALLBACK_PROT) callback_send, CLI_PCK_SIZE(send), true },
    { (CALLBACK_PROT) callback_messages, CLI_PCK_SIZE(messages), true },
    { (CALLBACK_PROT) callback_sub_team, CLI_PCK_SIZE(sub_team), true },
    { (CALLBACK_PROT) callback_sub_usr_team, CLI_PCK_SIZE(sub_usr_team), true },
    { (CALLBACK_PROT) callback_sub_list_teams, CLI_PCK_SIZE(sub_list_teams),
        true },
    { (CALLBACK_PROT) callback_unsub_team, CLI_PCK_SIZE(unsub_team), true },
    { (CALLBACK_PROT) callback_create_team, CLI_PCK_SIZE(create_team), true },
    { (CALLBACK_PROT) callback_create_chan, CLI_PCK_SIZE(create_chan), true },
    { (CALLBACK_PROT) callback_create_thread, CLI_PCK_SIZE(create_thread),
        true },
    { (CALLBACK_PROT) callback_create_reply, CLI_PCK_SIZE(create_reply), true },
    { (CALLBACK_PROT) callback_list_teams, CLI_PCK_SIZE(list_teams), true },
    { (CALLBACK_PROT) callback_list_chans, CLI_PCK_SIZE(list_chans), true },
    { (CALLBACK_PROT) callback_list_threads, CLI_PCK_SIZE(list_threads), true },
    { (CALLBACK_PROT) callback_list_replies, CLI_PCK_SIZE(list_replies), true },
    { (CALLBACK_PROT) callback_info_usr, CLI_PCK_SIZE(info_usr), true },
    { (CALLBACK_PROT) callback_info_team, CLI_PCK_SIZE(info_team), true },
    { (CALLBACK_PROT) callback_info_chan, CLI_PCK_SIZE(info_chan), true },
    { (CALLBACK_PROT) callback_info_thread, CLI_PCK_SIZE(info_thread), true },
    { (CALLBACK_PROT) callback_ping, CLI_PCK_SIZE(ping), false },
    { (CALLBACK_PROT) callback_set_comp, CLI_PCK_SIZE(set_comp), false },
    { (CALLBACK_PROT) callback_set_enc, CLI_PCK_SIZE(set_enc), false },
};

#endif /* !SERVER_CALLBACKS_H_ */