/*
** EPITECH PROJECT, 2021
** myteams
** File description:
** check_database_types
*/

#include "tools.h"

#include "server/database.h"

bool db_valid_user(json_object_t *user)
{
    return (user && (json_object_get_type(user, "timestamp") == j_number)
        && (json_object_get_type(user, "name") == j_string)
        && (strlen(json_object_get_string(user, "name")) <= MAX_NAME_LENGTH)
        && (json_object_get_type(user, "teams_sub") == j_array)
        && is_valid_str_uuids(json_object_get_array(user, "teams_sub")));
}

bool db_valid_message(json_object_t *message)
{
    return (message && (json_object_get_type(message, "timestamp") == j_number)
        && (json_object_get_type(message, "from") == j_string)
        && is_valid_str_uuid(json_object_get_string(message, "from"))
        && (json_object_get_type(message, "message") == j_string)
        && (strlen(json_object_get_string(message, "message"))
            <= MAX_BODY_LENGTH));
}

bool db_valid_thread(json_object_t *thread)
{
    json_object_t *messages = NULL;

    if (!thread || (json_object_get_type(thread, "messages") != j_object)
        || !db_valid_chat(thread))
        return false;
    messages = json_object_get_object(thread, "messages");
    JSON_OBJECT_ITERATE(it, messages)
    {
        if (!is_valid_str_uuid(json_it_get_key(it))
            || (json_it_get_type(it) != j_object)
            || !db_valid_message(json_it_get_object(it)))
            return false;
    }
    return true;
}

bool db_valid_channel(json_object_t *channel)
{
    json_object_t *threads = NULL;

    if (!channel || (json_object_get_type(channel, "threads") != j_object)
        || !db_valid_chat(channel))
        return false;
    threads = json_object_get_object(channel, "threads");
    JSON_OBJECT_ITERATE(it, threads)
    {
        if (!is_valid_str_uuid(json_it_get_key(it))
            || (json_it_get_type(it) != j_object)
            || !db_valid_thread(json_it_get_object(it)))
            return false;
    }
    return true;
}

bool db_valid_team(json_object_t *team)
{
    json_object_t *channels = NULL;

    if (!team || (json_object_get_type(team, "channels") != j_object)
        || !db_valid_chat(team)
        || (json_object_get_type(team, "users_sub") != j_array)
        || !is_valid_str_uuids(json_object_get_array(team, "users_sub")))
        return false;
    channels = json_object_get_object(team, "channels");
    JSON_OBJECT_ITERATE(it, channels)
    {
        if (!is_valid_str_uuid(json_it_get_key(it))
            || (json_it_get_type(it) != j_object)
            || !db_valid_channel(json_it_get_object(it)))
            return false;
    }
    return true;
}