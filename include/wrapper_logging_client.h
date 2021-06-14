/*
** EPITECH PROJECT, 2021
** WRAPPER_LOGGING_CLIENT
** File description:
** Wrapper_logging_client header
*/

#ifndef WRAPPER_LOGGING_CLIENT_H_
#define WRAPPER_LOGGING_CLIENT_H_

#include <time.h>

#include "tools.h"

#include "teams.h"

#include "myteams/logging_client.h"

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

#ifndef PARSE_RAW_DESC
#define PARSE_RAW_DESC(desc_raw, desc_str)                                     \
    char desc_str[MAX_DESCRIPTION_LENGTH + 1];                                 \
    exctract_desc_from_packet(desc_str, desc_raw);
#endif /* !PARSE_RAW_DESC */

#ifndef PARSE_RAW_BODY
#define PARSE_RAW_BODY(body_raw, body_str)                                     \
    char body_str[MAX_BODY_LENGTH + 1];                                        \
    exctract_body_from_packet(body_str, body_raw);
#endif /* !PARSE_RAW_BODY */

#define CLIENT_EVENT_LOGGED_IN(user_uuid, user_name)                           \
    {                                                                          \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_NAME(user_name, user_name_str);                              \
        client_event_logged_in(user_uuid_str, user_name_str);                  \
    }

#define CLIENT_EVENT_LOGGED_OUT(user_uuid, user_name)                          \
    {                                                                          \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_NAME(user_name, user_name_str);                              \
        client_event_logged_out(user_uuid_str, user_name_str);                 \
    }

#define CLIENT_EVENT_PRIVATE_MESSAGE_RECEIVED(user_uuid, message_body)         \
    {                                                                          \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_BODY(message_body, message_body_str);                        \
        client_event_private_message_received(                                 \
            user_uuid_str, message_body_str);                                  \
    }

#define CLIENT_EVENT_THREAD_REPLY_RECEIVED(                                    \
    team_uuid, thread_uuid, user_uuid, reply_body)                             \
    {                                                                          \
        UUID_UNPARSE(team_uuid, team_uuid_str);                                \
        UUID_UNPARSE(thread_uuid, thread_uuid_str);                            \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_BODY(reply_body, reply_body_str);                            \
        client_event_thread_reply_received(                                    \
            team_uuid_str, thread_uuid_str, user_uuid_str, reply_body_str);    \
    }

#define CLIENT_EVENT_TEAM_CREATED(team_uuid, team_name, team_description)      \
    {                                                                          \
        UUID_UNPARSE(team_uuid, team_uuid_str);                                \
        PARSE_RAW_NAME(team_name, team_name_str);                              \
        PARSE_RAW_DESC(team_description, team_description_str);                \
        client_event_team_created(                                             \
            team_uuid_str, team_name_str, team_description_str);               \
    }

#define CLIENT_EVENT_CHANNEL_CREATED(                                          \
    channel_uuid, channel_name, channel_description)                           \
    {                                                                          \
        UUID_UNPARSE(channel_uuid, channel_uuid_str);                          \
        PARSE_RAW_NAME(channel_name, channel_name_str);                        \
        PARSE_RAW_DESC(channel_description, channel_description_str);          \
        client_event_channel_created(                                          \
            channel_uuid_str, channel_name_str, channel_description_str);      \
    }

#define CLIENT_EVENT_THREAD_CREATED(                                           \
    thread_uuid, user_uuid, thread_timestamp, thread_title, thread_body)       \
    {                                                                          \
        UUID_UNPARSE(thread_uuid, thread_uuid_str);                            \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_NAME(thread_title, thread_title_str);                        \
        PARSE_RAW_BODY(thread_body, thread_body_str);                          \
        client_event_thread_created(thread_uuid_str, user_uuid_str,            \
            thread_timestamp, thread_title_str, thread_body_str);              \
    }

#define CLIENT_PRINT_USERS(user_uuid, user_name, user_status)                  \
    {                                                                          \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_NAME(user_name, user_name_str);                              \
        client_print_users(user_uuid_str, user_name_str, user_status);         \
    }

#define CLIENT_PRINT_TEAMS(team_uuid, team_name, team_description)             \
    {                                                                          \
        UUID_UNPARSE(team_uuid, team_uuid_str);                                \
        PARSE_RAW_NAME(team_name, team_name_str);                              \
        PARSE_RAW_DESC(team_description, team_description_str);                \
        client_print_teams(                                                    \
            team_uuid_str, team_name_str, team_description_str);               \
    }

#define CLIENT_TEAM_PRINT_CHANNELS(                                            \
    channel_uuid, channel_name, channel_description)                           \
    {                                                                          \
        UUID_UNPARSE(channel_uuid, channel_uuid_str);                          \
        PARSE_RAW_NAME(channel_name, channel_name_str);                        \
        PARSE_RAW_DESC(channel_description, channel_description_str);          \
        client_team_print_channels(                                            \
            channel_uuid_str, channel_name_str, channel_description_str);      \
    }

#define CLIENT_CHANNEL_PRINT_THREADS(                                          \
    thread_uuid, user_uuid, thread_timestamp, thread_title, thread_body)       \
    {                                                                          \
        UUID_UNPARSE(thread_uuid, thread_uuid_str);                            \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_NAME(thread_title, thread_title_str);                        \
        PARSE_RAW_BODY(thread_body, thread_body_str);                          \
        client_channel_print_threads(thread_uuid_str, user_uuid_str,           \
            thread_timestamp, thread_title_str, thread_body_str);              \
    }

#define CLIENT_THREAD_PRINT_REPLIES(                                           \
    thread_uuid, user_uuid, reply_timestamp, reply_body)                       \
    {                                                                          \
        UUID_UNPARSE(thread_uuid, thread_uuid_str);                            \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_BODY(reply_body, reply_body_str);                            \
        client_thread_print_replies(                                           \
            thread_uuid_str, user_uuid_str, reply_timestamp, reply_body_str);  \
    }

#define CLIENT_PRIVATE_MESSAGE_PRINT_MESSAGES(                                 \
    sender_uuid, message_timestamp, message_body)                              \
    {                                                                          \
        UUID_UNPARSE(sender_uuid, sender_uuid_str);                            \
        PARSE_RAW_BODY(message_body, message_body_str);                        \
        client_private_message_print_messages(                                 \
            sender_uuid_str, message_timestamp, message_body_str);             \
    }

#define CLIENT_ERROR_UNKNOWN_TEAM(team_uuid)                                   \
    {                                                                          \
        UUID_UNPARSE(team_uuid, team_uuid_str);                                \
        client_error_unknown_team(team_uuid_str);                              \
    }

#define CLIENT_ERROR_UNKNOWN_CHANNEL(channel_uuid)                             \
    {                                                                          \
        UUID_UNPARSE(channel_uuid, channel_uuid_str);                          \
        client_error_unknown_channel(channel_uuid_str);                        \
    }

#define CLIENT_ERROR_UNKNOWN_THREAD(thread_uuid)                               \
    {                                                                          \
        UUID_UNPARSE(thread_uuid, thread_uuid_str);                            \
        client_error_unknown_thread(thread_uuid_str);                          \
    }

#define CLIENT_ERROR_UNKNOWN_USER(user_uuid)                                   \
    {                                                                          \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        client_error_unknown_user(user_uuid_str);                              \
    }

#define CLIENT_ERROR_UNAUTHORIZED()                                            \
    {                                                                          \
        client_error_unauthorized();                                           \
    }

#define CLIENT_ERROR_ALREADY_EXIST()                                           \
    {                                                                          \
        client_error_already_exist();                                          \
    }

#define CLIENT_PRINT_USER(user_uuid, user_name, user_status)                   \
    {                                                                          \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_NAME(user_name, user_name_str);                              \
        client_print_user(user_uuid_str, user_name_str, user_status);          \
    }

#define CLIENT_PRINT_TEAM(team_uuid, team_name, team_description)              \
    {                                                                          \
        UUID_UNPARSE(team_uuid, team_uuid_str);                                \
        PARSE_RAW_NAME(team_name, team_name_str);                              \
        PARSE_RAW_DESC(team_description, team_description_str);                \
        client_print_team(team_uuid_str, team_name_str, team_description_str); \
    }

#define CLIENT_PRINT_CHANNEL(channel_uuid, channel_name, channel_description)  \
    {                                                                          \
        UUID_UNPARSE(channel_uuid, channel_uuid_str);                          \
        PARSE_RAW_NAME(channel_name, channel_name_str);                        \
        PARSE_RAW_DESC(channel_description, channel_description_str);          \
        client_print_channel(                                                  \
            channel_uuid_str, channel_name_str, channel_description_str);      \
    }

#define CLIENT_PRINT_THREAD(                                                   \
    thread_uuid, user_uuid, thread_timestamp, thread_title, thread_body)       \
    {                                                                          \
        UUID_UNPARSE(thread_uuid, thread_uuid_str);                            \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_NAME(thread_title, thread_title_str);                        \
        PARSE_RAW_BODY(thread_body, thread_body_str);                          \
        client_print_thread(thread_uuid_str, user_uuid_str, thread_timestamp,  \
            thread_title_str, thread_body_str);                                \
    }

#define CLIENT_PRINT_TEAM_CREATED(team_uuid, team_name, team_description)      \
    {                                                                          \
        UUID_UNPARSE(team_uuid, team_uuid_str);                                \
        PARSE_RAW_NAME(team_name, team_name_str);                              \
        PARSE_RAW_DESC(team_description, team_description_str);                \
        client_print_team_created(                                             \
            team_uuid_str, team_name_str, team_description_str);               \
    }

#define CLIENT_PRINT_CHANNEL_CREATED(                                          \
    channel_uuid, channel_name, channel_description)                           \
    {                                                                          \
        UUID_UNPARSE(channel_uuid, channel_uuid_str);                          \
        PARSE_RAW_NAME(channel_name, channel_name_str);                        \
        PARSE_RAW_DESC(channel_description, channel_description_str);          \
        client_print_channel_created(                                          \
            channel_uuid_str, channel_name_str, channel_description_str);      \
    }

#define CLIENT_PRINT_THREAD_CREATED(                                           \
    thread_uuid, user_uuid, thread_timestamp, thread_title, thread_body)       \
    {                                                                          \
        UUID_UNPARSE(thread_uuid, thread_uuid_str);                            \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_NAME(thread_title, thread_title_str);                        \
        PARSE_RAW_BODY(thread_body, thread_body_str);                          \
        client_print_thread_created(thread_uuid_str, user_uuid_str,            \
            thread_timestamp, thread_title_str, thread_body_str);              \
    }

#define CLIENT_PRINT_REPLY_CREATED(                                            \
    thread_uuid, user_uuid, reply_timestamp, reply_body)                       \
    {                                                                          \
        UUID_UNPARSE(thread_uuid, thread_uuid_str);                            \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        PARSE_RAW_BODY(reply_body, reply_body_str);                            \
        client_print_reply_created(                                            \
            thread_uuid_str, user_uuid_str, reply_timestamp, reply_body_str);  \
    }

#define CLIENT_PRINT_SUBSCRIBED(user_uuid, team_uuid)                          \
    {                                                                          \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        UUID_UNPARSE(team_uuid, team_uuid_str);                                \
        client_print_subscribed(user_uuid_str, team_uuid_str);                 \
    }

#define CLIENT_PRINT_UNSUBSCRIBED(user_uuid, team_uuid)                        \
    {                                                                          \
        UUID_UNPARSE(user_uuid, user_uuid_str);                                \
        UUID_UNPARSE(team_uuid, team_uuid_str);                                \
        client_print_unsubscribed(user_uuid_str, team_uuid_str);               \
    }

#endif /* !WRAPPER_LOGGING_CLIENT_H_ */