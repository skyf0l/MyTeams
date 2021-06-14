/*
** EPITECH PROJECT, 2021
** myteams
** File description:
** database
*/

#ifndef DATABASE_H_
#define DATABASE_H_

// SHOULD BE PRIVATE
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <uuid/uuid.h>

#include "server/teams_server.h"
#include "json/json.h"

#ifndef MAX_NAME_LENGTH
define MAX_NAME_LENGTH(32)
#endif /* !MAX_NAME_LENGTH */
#ifndef MAX_DESCRIPTION_LENGTH
#define MAX_DESCRIPTION_LENGTH (255)
#endif /* !MAX_DESCRIPTION_LENGTH */
#ifndef MAX_BODY_LENGTH
#define MAX_BODY_LENGTH (512)
#endif /* !MAX_BODY_LENGTH */

    static const char EMPTY_DATABASE[] =
        "{\"users\": {}, \"private_messages\": [], \"teams\": {}}";

typedef struct message {
    uuid_t from;
    uuid_t to;
    uuid_t msg_uuid;
    char message[MAX_BODY_LENGTH + 1];
    time_t timestamp;
} message_t;

typedef struct chat {
    uuid_t creator;
    uuid_t uuid;
    time_t timestamp;
    char name[MAX_NAME_LENGTH + 1];
    char desc[MAX_DESCRIPTION_LENGTH + 1];
} chat_t;

typedef struct msg_location {
    uuid_t team_uuid;
    uuid_t channel_uuid;
    uuid_t thread_uuid;
} msg_location_t;

// check database lists
bool db_valid_users(json_object_t *database);
bool db_valid_private_msgs(json_object_t *database);
bool db_valid_private_message(json_object_t *pm);
bool db_valid_teams(json_object_t *database);
bool is_valid_str_uuids(json_array_t *uuids);

// check database types
bool db_valid_user(json_object_t *user);
bool db_valid_message(json_object_t *message);
bool db_valid_thread(json_object_t *thread);
bool db_valid_channel(json_object_t *channel);
bool db_valid_team(json_object_t *team);

// check database generic objects / values
bool db_valid_chat(json_object_t *chat);

// create database types / objects
json_object_t *db_create_user(const char *username_infos);
json_object_t *db_create_pm(message_t *message_infos);
json_object_t *db_create_message(message_t *message_infos);
json_object_t *db_create_chat(chat_t *chat_infos, const char *sub_chat_name);

// SHOULD BE PUBLIC
// load safely server's database
json_object_t *db_load(const char *db_path, const char *empty_database);

// save database
bool db_save(json_object_t *database, const char *db_name);

// add elements to database
json_object_t *db_add_user(
    json_object_t *database, uuid_t uuid, const char *username);
bool db_add_private_message(json_object_t *db, message_t *message);
bool db_add_message(
    json_object_t *db, msg_location_t *location, message_t *message);
bool db_add_team(json_object_t *db, chat_t *chat_infos);
bool db_add_channel(
    json_object_t *db, const uuid_t team_uuid, chat_t *chat_infos);
bool db_add_thread(json_object_t *db, const uuid_t team_uuid,
    const uuid_t channel_uuid, chat_t *chat_infos);

// search element in database
json_object_t *db_get_user_by_id(json_object_t *users, const uuid_t user_id);
json_object_t *db_get_pm_by_user_id(
    json_object_t *database, const uuid_t usr1, const uuid_t usr2);
int db_search_sub_uuid(json_array_t *subs, const uuid_t to_find);
json_object_t *db_get_user_by_name(
    json_object_t *database, const char *username, uuid_t user_uuid);
json_object_t *db_get_team_by_name(json_object_t *db, const char *team_name);
json_object_t *db_get_channel_by_name(
    json_object_t *team, const char *chan_name);
json_object_t *db_get_thread_by_name(
    json_object_t *chan, const char *thread_name);
json_object_t *db_get_chat_by_name(json_object_t *chats, const char *chat_name);
json_object_t *db_get_team_by_uuid(json_object_t *db, const uuid_t team_uuid);
json_object_t *db_get_channel_by_uuid(
    json_object_t *team, const uuid_t chan_uuid);
json_object_t *db_get_thread_by_uuid(
    json_object_t *chan, const uuid_t thread_uuid);
json_object_t *db_get_chat_by_id(json_object_t *chats, const uuid_t chat_uuid);

// sub
bool db_subscribe_team(
    json_object_t *database, const uuid_t user_uuid, const uuid_t team_uuid);
bool db_unsubscribe_team(
    json_object_t *database, const uuid_t user_uuid, const uuid_t team_uuid);
bool db_is_sub_to_team(
    json_object_t *database, const uuid_t user_uuid, const uuid_t team_uuid);

bool db_is_user_logged_in(json_object_t *database, const uuid_t user_uuid);

bool db_fill_chat_from_it(json_it_t *chat_it, chat_t *chat_info);
bool db_fill_chat(
    json_object_t *chat, const uuid_t chat_uuid, chat_t *chat_info);

#endif /* !DATABASE_H_ */