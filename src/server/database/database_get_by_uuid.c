/*
** EPITECH PROJECT, 2021
** myteams
** File description:
** database_get_by_uuid
*/

#include "server/database.h"

json_object_t *db_get_user_by_id(json_object_t *users, const uuid_t user_id)
{
    char uuid_str[UUID_STR_LEN];

    users = json_object_get_object(users, "users");
    uuid_unparse_lower(user_id, uuid_str);
    return json_object_get_object(users, uuid_str);
}

json_object_t *db_get_pm_by_user_id(
    json_object_t *database, const uuid_t usr1, const uuid_t usr2)
{
    json_array_t *pms = json_object_get_array(database, "private_messages");
    json_object_t *pm = NULL;
    json_array_t *users = NULL;
    char usr1_str[UUID_STR_LEN];
    char usr2_str[UUID_STR_LEN];

    uuid_unparse_lower(usr1, usr1_str);
    uuid_unparse_lower(usr2, usr2_str);
    JSON_ARRAY_ITERATE(it, id, pms) {
        pm = json_it_get_object(it);
        users = json_object_get_array(pm, "users");
        if (!pm || !users)
            continue;
        if ((!strcmp(usr1_str, json_array_get_string(users, 0))
                && !strcmp(usr2_str, json_array_get_string(users, 1)))
            || (!strcmp(usr1_str, json_array_get_string(users, 1))
                && !strcmp(usr2_str, json_array_get_string(users, 0))))
            return pm;
    }
    return NULL;
}

int db_search_sub_uuid(json_array_t *subs, const uuid_t to_find)
{
    char to_find_str[UUID_STR_LEN];

    uuid_unparse_lower(to_find, to_find_str);
    JSON_ARRAY_ITERATE(it, res_id, subs)
    {
        if (json_it_get_type(it) != j_string)
            continue;
        if (!strcmp(json_it_get_string(it), to_find_str))
            return res_id;
    }
    return -1;
}
