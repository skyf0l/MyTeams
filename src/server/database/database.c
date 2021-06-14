/*
** EPITECH PROJECT, 2021
** myteams
** File description:
** database
*/

#include "server/database.h"

json_object_t *db_load(const char *db_path, const char *empty_database)
{
    json_object_t *database = json_object_create_from_file(db_path);

    if (!database
        || !db_valid_users(database)
        || !db_valid_private_msgs(database)
        || !db_valid_teams(database)) {
        json_object_destroy(database);
        database = json_object_create_from_string(empty_database);
    }
    return database;
}

bool db_save(json_object_t *database, const char *db_name)
{
    return !json_object_save_to_file(database, db_name);
}