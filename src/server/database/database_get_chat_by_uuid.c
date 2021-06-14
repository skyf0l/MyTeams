/*
** EPITECH PROJECT, 2021
** myteams
** File description:
** database_get_chat_by_uuid
*/

#include "server/database.h"

json_object_t *db_get_chat_by_id(json_object_t *chats, const uuid_t chat_uuid)
{
    char uuid_thread_str[37];

    uuid_unparse_lower(chat_uuid, uuid_thread_str);
    return json_object_get_object(chats, uuid_thread_str);
}

json_object_t *db_get_team_by_uuid(json_object_t *db, const uuid_t team_uuid)
{
    db = json_object_get_object(db, "teams");
    return db_get_chat_by_id(db, team_uuid);
}

json_object_t *db_get_channel_by_uuid(
    json_object_t *team, const uuid_t chan_uuid)
{
    team = json_object_get_object(team, "channels");
    return db_get_chat_by_id(team, chan_uuid);
}

json_object_t *db_get_thread_by_uuid(
    json_object_t *chan, const uuid_t thread_uuid)
{
    chan = json_object_get_object(chan, "threads");
    return db_get_chat_by_id(chan, thread_uuid);
}