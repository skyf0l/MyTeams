/*
** EPITECH PROJECT, 2021
** myteams
** File description:
** database_add
*/

#include "server/database.h"

json_object_t *db_create_user(const char *username)
{
    json_object_t *new_user = json_object_create();
    json_object_t *new_uuid_arr = json_array_create();

    if (!new_user || json_object_put_long(new_user, "timestamp", time(NULL))
        || json_object_put_string(new_user, "name", username)
        || json_object_put_array(new_user, "teams_sub", new_uuid_arr)) {
        json_object_destroy(new_user);
        json_array_destroy(new_uuid_arr);
        return NULL;
    }
    return new_user;
}

json_object_t *db_add_user(
    json_object_t *database, uuid_t uuid, const char *username)
{
    json_object_t *new_user = NULL;
    json_object_t *users = json_object_get_object(database, "users");
    char uuid_str[37];

    uuid_generate_random(uuid);
    uuid_unparse_lower(uuid, uuid_str);
    new_user = db_create_user(username);
    if (!new_user) {
        return NULL;
    }
    if (json_object_put_object(users, uuid_str, new_user))
        return NULL;
    return new_user;
}
