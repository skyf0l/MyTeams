/*
** EPITECH PROJECT, 2021
** myteams
** File description:
** database_get_by_name
*/

#include "server/database.h"

json_object_t *db_get_user_by_name(
    json_object_t *database, const char *username, uuid_t user_uuid)
{
    json_object_t *user = NULL;

    database = json_object_get_object(database, "users");
    JSON_OBJECT_ITERATE(it, database)
    {
        user = json_it_get_object(it);
        if (!strcmp(username, json_object_get_string(user, "name"))) {
            uuid_parse(json_it_get_key(it), user_uuid);
            return user;
        }
    }
    return NULL;
}

json_object_t *db_get_team_by_name(json_object_t *db, const char *team_name)
{
    db = json_object_get_object(db, "teams");
    return db_get_chat_by_name(db, team_name);
}

json_object_t *db_get_channel_by_name(
    json_object_t *team, const char *chan_name)
{
    team = json_object_get_object(team, "channels");
    return db_get_chat_by_name(team, chan_name);
}

json_object_t *db_get_thread_by_name(
    json_object_t *chan, const char *thread_name)
{
    chan = json_object_get_object(chan, "threads");
    return db_get_chat_by_name(chan, thread_name);
}

json_object_t *db_get_chat_by_name(json_object_t *chats, const char *chat_name)
{
    json_object_t *chat = NULL;

    JSON_OBJECT_ITERATE(it, chats)
    {
        chat = json_it_get_object(it);
        if (!strcmp(chat_name, json_object_get_string(chat, "name")))
            return chat;
    }
    return NULL;
}