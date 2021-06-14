/*
** EPITECH PROJECT, 2021
** myteams
** File description:
** test_database_add
*/

#include "server/database.h"
#include <criterion/criterion.h>

Test(add_user, basic_1_usr)
{
    json_object_t *database = db_load("add_1_user_basic.json", EMPTY_DATABASE);
    uuid_t id_test;

    cr_assert(db_add_user(database, id_test, "usr_name_test"));
    cr_assert_not(uuid_is_null(id_test));
    cr_assert(db_save(database, "add_1_user_basic.json"));
}

Test(add_user, basic_3_usrs)
{
    json_object_t *database = db_load("add_3_users_basic.json", EMPTY_DATABASE);
    uuid_t id_test;

    db_add_user(database, id_test, "usr_name_test_1");
    cr_assert_not(uuid_is_null(id_test));
    db_add_user(database, id_test, "usr_name_test_2");
    cr_assert_not(uuid_is_null(id_test));
    db_add_user(database, id_test, "usr_name_test_3");
    cr_assert_not(uuid_is_null(id_test));
    cr_assert(db_save(database, "add_3_users_basic.json"));
}

Test(add_pm, basic_2_msg)
{
    json_object_t *database = db_load("add_1_msg_basic.json", EMPTY_DATABASE);
    uuid_t id_usr3;
    message_t msg;

    db_add_user(database, msg.from, "usr_name_test_1");
    cr_assert_not(uuid_is_null(msg.from));
    db_add_user(database, msg.to, "usr_name_test_2");
    cr_assert_not(uuid_is_null(msg.to));
    db_add_user(database, id_usr3, "usr_name_test_3");
    cr_assert_not(uuid_is_null(id_usr3));
    strcpy(msg.message, "test1");
    cr_assert(db_add_private_message(database, &msg));
    strcpy(msg.message, "test2");
    cr_assert(db_add_private_message(database, &msg));
    cr_assert_not(uuid_is_null(msg.msg_uuid));
    cr_assert(db_save(database, "add_1_msg_basic.json"));
}

Test(add_team, basic_1_team)
{
    json_object_t *database = db_load("add_team_basic.json", EMPTY_DATABASE);
    chat_t team_info;
    uuid_t id_test;

    db_add_user(database, id_test, "usr_name_test");
    strcpy(team_info.name, "Test1");
    strcpy(team_info.desc, "Test to add a team");
    memcpy(team_info.creator, id_test, sizeof(uuid_t));
    cr_assert(db_add_team(database, &team_info));
    cr_assert(db_save(database, "add_team_basic.json"));
}

Test(add_channel, basic_1_channel)
{
    json_object_t *database = db_load("add_channel_basic.json", EMPTY_DATABASE);
    chat_t team_info;
    chat_t channel_info;
    uuid_t id_test;

    db_add_user(database, id_test, "usr_name_test");
    strcpy(team_info.name, "Test1");
    strcpy(team_info.desc, "Test to add a team");
    memcpy(team_info.creator, id_test, sizeof(uuid_t));
    cr_assert(db_add_team(database, &team_info));
    strcpy(channel_info.name, "TestC");
    strcpy(channel_info.desc, "Test to add a channel in a team");
    memcpy(channel_info.creator, id_test, sizeof(uuid_t));
    cr_assert(db_add_channel(database, team_info.uuid, &channel_info));
    cr_assert(db_save(database, "add_channel_basic.json"));
}

Test(add_thread, basic_1_thread)
{
    json_object_t *database = db_load("add_thread_basic.json", EMPTY_DATABASE);
    chat_t team_info;
    chat_t channel_info;
    chat_t thread_info;
    uuid_t id_test;

    db_add_user(database, id_test, "usr_name_test");
    strcpy(team_info.name, "Test1");
    strcpy(team_info.desc, "Test to add a team");
    memcpy(team_info.creator, id_test, sizeof(uuid_t));
    cr_assert(db_add_team(database, &team_info));
    strcpy(channel_info.name, "TestC");
    strcpy(channel_info.desc, "Test to add a channel in a team");
    memcpy(channel_info.creator, id_test, sizeof(uuid_t));
    cr_assert(db_add_channel(database, team_info.uuid, &channel_info));
    strcpy(thread_info.name, "TestT");
    strcpy(thread_info.desc, "Test to add a thread in a channel");
    memcpy(thread_info.creator, id_test, sizeof(uuid_t));
    cr_assert(db_add_thread(
        database, team_info.uuid, channel_info.uuid, &thread_info));
    cr_assert(db_save(database, "add_thread_basic.json"));
}

Test(add_message, basic_1_message)
{
    json_object_t *database = db_load("add_message_basic.json", EMPTY_DATABASE);
    chat_t team_info;
    chat_t channel_info;
    chat_t thread_info;
    message_t msg;
    msg_location_t location;
    uuid_t id_test;

    db_add_user(database, id_test, "usr_name_test");
    strcpy(team_info.name, "Test1");
    strcpy(team_info.desc, "Test to add a team");
    memcpy(team_info.creator, id_test, sizeof(uuid_t));
    cr_assert(db_add_team(database, &team_info));
    strcpy(channel_info.name, "TestC");
    strcpy(channel_info.desc, "Test to add a channel in a team");
    memcpy(channel_info.creator, id_test, sizeof(uuid_t));
    cr_assert(db_add_channel(database, team_info.uuid, &channel_info));
    strcpy(thread_info.name, "TestT");
    strcpy(thread_info.desc, "Test to add a thread in a channel");
    memcpy(thread_info.creator, id_test, sizeof(uuid_t));
    cr_assert(db_add_thread(
        database, team_info.uuid, channel_info.uuid, &thread_info));
    memcpy(msg.message, "Test to add a message in a thread",
        sizeof("Test to add a message in a thread"));
    memcpy(msg.from, id_test, sizeof(uuid_t));
    memcpy(location.team_uuid, team_info.uuid, sizeof(uuid_t));
    memcpy(location.channel_uuid, channel_info.uuid, sizeof(uuid_t));
    memcpy(location.thread_uuid, thread_info.uuid, sizeof(uuid_t));
    cr_assert(db_add_message(database, &location, &msg));
    cr_assert(db_save(database, "add_message_basic.json"));
}