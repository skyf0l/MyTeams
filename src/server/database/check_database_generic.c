/*
** EPITECH PROJECT, 2021
** myteams
** File description:
** check_database_generic
*/

#include "tools.h"

#include "server/database.h"

bool db_valid_chat(json_object_t *chat)
{
    return ((json_object_get_type(chat, "timestamp") == j_number)
        && (json_object_get_type(chat, "name") == j_string)
        && (strlen(json_object_get_string(chat, "name")) <= MAX_NAME_LENGTH)
        && (json_object_get_type(chat, "description") == j_string)
        && (strlen(json_object_get_string(chat, "description"))
            <= MAX_DESCRIPTION_LENGTH)
        && (json_object_get_type(chat, "creator") == j_string)
        && is_valid_str_uuid(json_object_get_string(chat, "creator")));
}