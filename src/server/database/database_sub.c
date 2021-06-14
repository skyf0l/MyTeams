/*
** EPITECH PROJECT, 2021
** myteams
** File description:
** database_sub
*/

#include "server/database.h"

bool db_is_sub_to_team(
    json_object_t *database, const uuid_t user_uuid, const uuid_t team_uuid)
{
    json_object_t *user = db_get_user_by_id(database, user_uuid);
    json_object_t *team =
        db_get_chat_by_id(json_object_get_object(database, "teams"), team_uuid);
    json_array_t *user_teams = json_object_get_array(user, "teams_sub");
    json_array_t *team_users = json_object_get_array(team, "users_sub");
    char uuid_user_str[37];
    char uuid_team_str[37];

    uuid_unparse_lower(user_uuid, uuid_user_str);
    uuid_unparse_lower(team_uuid, uuid_team_str);
    if (!user_teams || !team_users)
        return false;
    return (db_search_sub_uuid(user_teams, team_uuid) != -1
        && db_search_sub_uuid(team_users, user_uuid) != -1);
}

bool db_subscribe_team(
    json_object_t *database, const uuid_t user_uuid, const uuid_t team_uuid)
{
    json_object_t *user = db_get_user_by_id(database, user_uuid);
    json_object_t *team =
        db_get_chat_by_id(json_object_get_object(database, "teams"), team_uuid);
    json_array_t *user_teams = json_object_get_array(user, "teams_sub");
    json_array_t *team_users = json_object_get_array(team, "users_sub");
    char uuid_user_str[37];
    char uuid_team_str[37];

    uuid_unparse_lower(user_uuid, uuid_user_str);
    uuid_unparse_lower(team_uuid, uuid_team_str);
    if (!user_teams || !team_users)
        return false;
    if (db_search_sub_uuid(user_teams, team_uuid) == -1
        && json_array_put_string(user_teams, uuid_team_str))
        return false;
    if (db_search_sub_uuid(team_users, user_uuid) == -1
        && json_array_put_string(team_users, uuid_user_str))
        return false;
    return true;
}

bool db_unsubscribe_team(
    json_object_t *database, const uuid_t user_uuid, const uuid_t team_uuid)
{
    json_object_t *user = db_get_user_by_id(database, user_uuid);
    json_object_t *team =
        db_get_chat_by_id(json_object_get_object(database, "teams"), team_uuid);
    json_array_t *user_teams = json_object_get_array(user, "teams_sub");
    json_array_t *team_users = json_object_get_array(team, "users_sub");
    int user_id;
    int team_id;

    if (!user_teams || !team_users)
        return false;
    while ((team_id = db_search_sub_uuid(user_teams, team_uuid)) != -1) {
        if (json_array_remove(user_teams, team_id))
            return false;
    }
    while ((user_id = db_search_sub_uuid(team_users, user_uuid)) != -1) {
        if (json_array_remove(team_users, user_id))
            return false;
    }
    return true;
}