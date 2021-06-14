/*
** EPITECH PROJECT, 2021
** myteams
** File description:
** database_add_team
*/

#include "server/database.h"

json_object_t *db_create_chat(chat_t *chat_infos, const char *sub_chat_name)
{
    json_object_t *chat = json_object_create();
    json_object_t *sub_chat = json_object_create();
    char uuid_creator[37];

    if (!chat || !sub_chat || !sub_chat_name)
        return NULL;
    chat_infos->timestamp = time(NULL);
    uuid_unparse_lower(chat_infos->creator, uuid_creator);
    if (json_object_put_long(chat, "timestamp", chat_infos->timestamp)
        || json_object_put_string(chat, "name", chat_infos->name)
        || json_object_put_string(chat, "description", chat_infos->desc)
        || json_object_put_string(chat, "creator", uuid_creator)
        || json_object_put_object(chat, sub_chat_name, sub_chat)) {
        json_object_destroy(chat);
        return NULL;
    }
    return chat;
}

bool db_add_team(json_object_t *chats, chat_t *chat_infos)
{
    json_object_t *team = json_object_get_object(chats, "teams");
    json_object_t *chat = NULL;
    json_array_t *users_sub = NULL;
    char uuid_chat[37];

    uuid_generate_random(chat_infos->uuid);
    uuid_unparse_lower(chat_infos->uuid, uuid_chat);
    chat = db_create_chat(chat_infos, "channels");
    if (!chat)
        return false;
    users_sub = json_array_create();
    if (!chats || !users_sub
        || json_object_put_array(chat, "users_sub", users_sub)
        || json_object_put_object(team, uuid_chat, chat)) {
        json_array_destroy(users_sub);
        json_object_destroy(chat);
        return false;
    }
    return true;
}

bool db_add_channel(
    json_object_t *chats, const uuid_t team_uuid, chat_t *chat_infos)
{
    json_object_t *chat = NULL;
    char uuid_chat[37];

    chats = json_object_get_object(chats, "teams");
    chats =
        json_object_get_object(db_get_chat_by_id(chats, team_uuid), "channels");
    uuid_generate_random(chat_infos->uuid);
    uuid_unparse_lower(chat_infos->uuid, uuid_chat);
    chat = db_create_chat(chat_infos, "threads");
    if (!chat)
        return false;
    if (!chats || json_object_put_object(chats, uuid_chat, chat)) {
        json_object_destroy(chat);
        return false;
    }
    return true;
}

bool db_add_thread(json_object_t *chats, const uuid_t team_uuid,
    const uuid_t channel_uuid, chat_t *chat_infos)
{
    json_object_t *chat = NULL;
    char uuid_chat[37];

    chats = json_object_get_object(chats, "teams");
    chats =
        json_object_get_object(db_get_chat_by_id(chats, team_uuid), "channels");
    chats = json_object_get_object(
        db_get_chat_by_id(chats, channel_uuid), "threads");
    uuid_generate_random(chat_infos->uuid);
    uuid_unparse_lower(chat_infos->uuid, uuid_chat);
    chat = db_create_chat(chat_infos, "messages");
    if (!chat)
        return false;
    if (!chats || json_object_put_object(chats, uuid_chat, chat)) {
        json_object_destroy(chat);
        return false;
    }
    return true;
}