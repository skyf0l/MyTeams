/*
** EPITECH PROJECT, 2021
** WRAPPER_LOGGING_SERVER
** File description:
** Wrapper_logging_server header
*/

#ifndef WRAPPER_LOGGING_SERVER_H_
#define WRAPPER_LOGGING_SERVER_H_

#include "tools.h"

#include "teams.h"

#include "myteams/logging_server.h"

#ifndef UUID_UNPARSE
#define UUID_UNPARSE(uuid_var, uuid_var_str)                                   \
    char uuid_var_str[37];                                                     \
    uuid_unparse_lower(uuid_var, uuid_var_str);
#endif /* !UUID_UNPARSE */

#ifndef PARSE_RAW_NAME
#define PARSE_RAW_NAME(name_raw, name_str)                                     \
    char name_str[MAX_NAME_LENGTH + 1];                                        \
    exctract_name_from_packet(name_str, name_raw);
#endif /* !PARSE_RAW_NAME */

#ifndef PARSE_RAW_BODY
#define PARSE_RAW_BODY(body_raw, body_str)                                     \
    char body_str[MAX_BODY_LENGTH + 1];                                        \
    exctract_body_from_packet(body_str, body_raw);
#endif /* !PARSE_RAW_BODY */

#define SERVER_EVENT_TEAM_CREATED(team_uuid, team_name, user_uuid)             \
    {                                                                          \
        UUID_UNPARSE(team_uuid, team_uuid_str);                                \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_NAME(team_name, team_name_str);                              \
        server_event_team_created(                                             \
            team_uuid_str, team_name_str, user_uuid_str);                      \
    }

#define SERVER_EVENT_CHANNEL_CREATED(team_uuid, channel_uuid, channel_name)    \
    {                                                                          \
        UUID_UNPARSE(team_uuid, team_uuid_str);                                \
        UUID_UNPARSE(channel_uuid, channel_uuid_str);                          \
        PARSE_RAW_NAME(channel_name, channel_name_str);                        \
        server_event_channel_created(                                          \
            team_uuid_str, channel_uuid_str, channel_name_str);                \
    }

#define SERVER_EVENT_THREAD_CREATED(                                           \
    channel_uuid, thread_uuid, user_uuid, thread_title, thread_body)           \
    {                                                                          \
        UUID_UNPARSE(channel_uuid, channel_uuid_str);                          \
        UUID_UNPARSE(thread_uuid, thread_uuid_str);                            \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_NAME(thread_title, thread_title_str);                        \
        PARSE_RAW_BODY(thread_body, thread_body_str);                          \
        server_event_thread_created(channel_uuid_str, thread_uuid_str,         \
            user_uuid_str, thread_title_str, thread_body_str);                 \
    }

#define SERVER_EVENT_REPLY_CREATED(thread_uuid, user_uuid, reply_body)         \
    {                                                                          \
        UUID_UNPARSE(thread_uuid, thread_uuid_str);                            \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_BODY(reply_body, reply_body_str);                            \
        server_event_reply_created(                                            \
            thread_uuid_str, user_uuid_str, reply_body_str);                   \
    }

#define SERVER_EVENT_USER_SUBSCRIBED(team_uuid, user_uuid)                     \
    {                                                                          \
        UUID_UNPARSE(team_uuid, team_uuid_str);                                \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        server_event_user_subscribed(team_uuid_str, user_uuid_str);            \
    }

#define SERVER_EVENT_USER_UNSUBSCRIBED(team_uuid, user_uuid)                   \
    {                                                                          \
        UUID_UNPARSE(team_uuid, team_uuid_str);                                \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        server_event_user_unsubscribed(team_uuid_str, user_uuid_str);          \
    }

#define SERVER_EVENT_USER_CREATED(user_uuid, user_name)                        \
    {                                                                          \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_NAME(user_name, user_name_str);                              \
        server_event_user_created(user_uuid_str, user_name_str);               \
    }

#define SERVER_EVENT_USER_LOADED(user_uuid, user_name)                         \
    {                                                                          \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_NAME(user_name, user_name_str);                              \
        server_event_user_loaded(user_uuid_str, user_name_str);                \
    }

#define SERVER_EVENT_USER_LOGGED_IN(user_uuid)                                 \
    {                                                                          \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        server_event_user_logged_in(user_uuid_str);                            \
    }

#define SERVER_EVENT_USER_LOGGED_OUT(user_uuid)                                \
    {                                                                          \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        server_event_user_logged_out(user_uuid_str);                           \
    }

#define SERVER_EVENT_PRIVATE_MESSAGE_SENDED(                                   \
    sender_uuid, receiver_uuid, message_body)                                  \
    {                                                                          \
        UUID_UNPARSE(sender_uuid, sender_uuid_str);                            \
        UUID_UNPARSE(receiver_uuid, receiver_uuid_str);                        \
        PARSE_RAW_BODY(message_body, message_body_str);                        \
        server_event_private_message_sended(                                   \
            sender_uuid_str, receiver_uuid_str, message_body_str);             \
    }

#endif /* !WRAPPER_LOGGING_SERVER_H_ */