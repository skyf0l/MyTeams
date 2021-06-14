/*
** EPITECH PROJECT, 2021
** DATABASE_FILL_CHAT
** File description:
** Database_fill_chat function
*/

#include "tools.h"

#include "server/database.h"

bool db_fill_chat_from_it(json_it_t *chat_it, chat_t *chat_info)
{
    char *key = json_it_get_key(chat_it);
    json_object_t *team = json_it_get_object(chat_it);
    char *name = json_object_get_string(team, "name");
    char *desc = json_object_get_string(team, "description");
    char *creator = json_object_get_string(team, "creator");

    if (!key || !team || !name || !desc || !creator)
        return false;
    memset(chat_info, 0, sizeof(chat_t));
    exctract_name_from_packet(chat_info->name, name);
    exctract_desc_from_packet(chat_info->desc, desc);
    uuid_parse(key, chat_info->uuid);
    uuid_parse(creator, chat_info->creator);
    chat_info->timestamp = json_object_get_long(team, "timestamp");
    return true;
}

bool db_fill_chat(
    json_object_t *chat, const uuid_t chat_uuid, chat_t *chat_info)
{
    char *name = json_object_get_string(chat, "name");
    char *desc = json_object_get_string(chat, "description");
    char *creator = json_object_get_string(chat, "creator");

    if (!chat || !name || !desc || !creator)
        return false;
    copy_uuid(chat_info->uuid, chat_uuid);
    exctract_name_from_packet(chat_info->name, name);
    exctract_desc_from_packet(chat_info->desc, desc);
    uuid_parse(creator, chat_info->creator);
    chat_info->timestamp = json_object_get_long(chat, "timestamp");
    return true;
}