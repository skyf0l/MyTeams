/*
** EPITECH PROJECT, 2021
** myteams
** File description:
** tests_database_creation
*/

#include <criterion/criterion.h>
#include "server/database.h"

Test(database_init, basic)
{
    json_object_t *database = db_load("db_init.json", EMPTY_DATABASE);

    cr_assert_not_null(database);
    cr_assert(db_save(database, "db_init.json"));
}

Test(save_null, basic)
{
    cr_assert_not(db_save(NULL, ""));
}

Test(restart, user_2_save)
{
    json_object_t *database = db_load("db_restart_user.json", EMPTY_DATABASE);
    uuid_t user_uuid1;
    uuid_t user_uuid2;

    cr_assert_not_null(database);
    cr_assert(db_add_user(database, user_uuid1, "to_save"));
    cr_assert(db_add_user(database, user_uuid2, "to_save2"));

    cr_assert(db_save(database, "db_restart_user.json"));

    json_object_destroy(database);
    database = db_load("db_restart_user.json", EMPTY_DATABASE);
    cr_assert_not_null(database);
    cr_assert(db_save(database, "db_restart_user.json"));
}

Test(restart, pm_save)
{
    json_object_t *database = db_load("db_restart_pm.json", EMPTY_DATABASE);
    message_t message;

    cr_assert_not_null(database);
    cr_assert(db_add_user(database, message.from, "to_save"));
    cr_assert(db_add_user(database, message.to, "to_save2"));
    cr_assert_not(uuid_is_null(message.from));
    cr_assert_not(uuid_is_null(message.to));
    strcpy(message.message, "msg_to_save");
    cr_assert(db_add_private_message(database, &message));
    cr_assert(db_save(database, "db_restart_pm.json"));
    json_object_destroy(database);
    database = db_load("db_restart_pm.json", EMPTY_DATABASE);
    cr_assert_not_null(database);
    cr_assert(db_save(database, "db_restart_pm.json"));
}