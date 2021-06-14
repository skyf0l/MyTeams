/*
** EPITECH PROJECT, 2021
** DATABASE_IS_USER_LOGGED_IN
** File description:
** Database_is_user_logged_in function
*/

#include "server/database.h"

bool db_is_user_logged_in(json_object_t *database, const uuid_t user_uuid)
{
    json_object_t *user = db_get_user_by_id(database, user_uuid);

    if (!user)
        return false;
    return !!json_object_get_int(user, "status");
}