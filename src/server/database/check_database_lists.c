/*
** EPITECH PROJECT, 2021
** myteams
** File description:
** check_database_lists
*/

#include "tools.h"

#include "server/database.h"

bool db_valid_users(json_object_t *database)
{
    json_object_t *users = NULL;
    if (!database || (json_object_get_type(database, "users") != j_object))
        return false;
    users = json_object_get_object(database, "users");
    JSON_OBJECT_ITERATE(it, users)
    {
        if (!is_valid_str_uuid(json_it_get_key(it))
            || (json_it_get_type(it) != j_object)
            || !db_valid_user(json_it_get_object(it)))
            return false;
    }
    return true;
}

bool db_valid_private_msgs(json_object_t *database)
{
    json_array_t *private_messages = NULL;

    if (!database
        || (json_object_get_type(database, "private_messages") != j_array))
        return false;
    private_messages = json_object_get_array(database, "private_messages");
    JSON_ARRAY_ITERATE(it, id, private_messages)
    {
        if (json_it_get_type(it) != j_object
            || !db_valid_private_message(json_it_get_object(it)))
            return false;
    }
    return true;
}

bool db_valid_private_message(json_object_t *pm)
{
    json_array_t *users = NULL;

    if (!pm)
        return false;
    users = json_object_get_array(pm, "users");
    if (!users || (users->elements_count != 2)
        || (json_array_get_type(users, 0) != j_string)
        || !is_valid_str_uuid(json_array_get_string(users, 0))
        || (json_array_get_type(users, 1) != j_string)
        || !is_valid_str_uuid(json_array_get_string(users, 1))
        || json_object_get_type(pm, "messages") != j_object
        || !(pm = json_object_get_object(pm, "messages")))
        return false;
    JSON_OBJECT_ITERATE(it, pm) {
        if (!is_valid_str_uuid(json_it_get_key(it))
            || (json_it_get_type(it) != j_object)
            || !db_valid_message(json_it_get_object(it)))
            return false;
    }
    return true;
}

bool db_valid_teams(json_object_t *database)
{
    json_object_t *teams = NULL;
    if (!database || (json_object_get_type(database, "teams") != j_object))
        return false;
    teams = json_object_get_object(database, "teams");
    JSON_OBJECT_ITERATE(it, teams)
    {
        if (!is_valid_str_uuid(json_it_get_key(it))
            || (json_it_get_type(it) != j_object)
            || !db_valid_team(json_it_get_object(it)))
            return false;
    }
    return true;
}

bool is_valid_str_uuids(json_array_t *uuids)
{
    if (!uuids)
        return false;
    JSON_ARRAY_ITERATE(it, id, uuids)
    {
        if (json_it_get_type(it) != j_string
            || !is_valid_str_uuid(json_it_get_string(it)))
            return false;
    }
    return true;
}