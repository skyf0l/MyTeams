/*
** EPITECH PROJECT, 2021
** myteams
** File description:
** database_add_pm
*/

#include "server/database.h"

json_array_t *db_create_user_pair(uuid_t uuid_1, uuid_t uuid_2)
{
    json_array_t *users = json_array_create();
    char uuid_str_1[UUID_STR_LEN];
    char uuid_str_2[UUID_STR_LEN];

    uuid_unparse_lower(uuid_1, uuid_str_1);
    uuid_unparse_lower(uuid_2, uuid_str_2);
    if (!users)
        return NULL;
    if (json_array_put_string(users, uuid_str_1)
        || json_array_put_string(users, uuid_str_2)) {
        return json_array_destroy(users);
    }
    return users;
}

json_object_t *db_create_pm(message_t *message)
{
    json_object_t *pm = json_object_create();
    json_array_t *users = db_create_user_pair(message->from, message->to);
    json_object_t *msgs = json_object_create();
    json_object_t *msg = db_create_message(message);
    char uuid_msg[UUID_STR_LEN];

    uuid_unparse_lower(message->msg_uuid, uuid_msg);
    if (!pm || !users || !msgs || !msg) {
        json_object_destroy(pm);
        json_array_destroy(users);
        json_object_destroy(msgs);
        json_object_destroy(msg);
        return NULL;
    }
    if (json_object_put_array(pm, "users", users)
        || json_object_put_object(pm, "messages", msgs)
        || json_object_put_object(msgs, uuid_msg, msg))
        return json_array_destroy(pm);
    return pm;
}

json_object_t *db_create_message(message_t *message)
{
    json_object_t *new_msg = NULL;
    char uuid_from[37];

    uuid_unparse_lower(message->from, uuid_from);
    message->timestamp = time(NULL);
    new_msg = json_object_create();
    if (!new_msg
        || json_object_put_long(new_msg, "timestamp", message->timestamp)
        || json_object_put_string(new_msg, "from", uuid_from)
        || json_object_put_string(new_msg, "message", message->message)) {
        json_object_destroy(new_msg);
        return NULL;
    }
    return new_msg;
}

bool db_add_private_message(json_object_t *database, message_t *message)
{
    json_array_t *private_messages =
        json_object_get_array(database, "private_messages");
    json_object_t *new_pm = NULL;
    json_object_t *pms = NULL;
    bool db_is_add;
    char msg_uuid[37];

    uuid_generate_random(message->msg_uuid);
    pms = db_get_pm_by_user_id(database, message->from, message->to);
    if (pms) {
        new_pm = db_create_message(message);
        uuid_unparse_lower(message->msg_uuid, msg_uuid);
        db_is_add = !json_object_put_object(
            json_object_get_object(pms, "messages"), msg_uuid, new_pm);
    } else {
        new_pm = db_create_pm(message);
        db_is_add = !json_array_put_object(private_messages, new_pm);
    }
    if (!db_is_add)
        json_object_destroy(new_pm);
    return (private_messages && new_pm && db_is_add);
}

bool db_add_message(
    json_object_t *messages, msg_location_t *location, message_t *message)
{
    json_object_t *msg = NULL;
    char uuid_msg[37];

    messages = json_object_get_object(messages, "teams");
    messages = db_get_chat_by_id(messages, location->team_uuid);
    messages = json_object_get_object(messages, "channels");
    messages = db_get_chat_by_id(messages, location->channel_uuid);
    messages = json_object_get_object(messages, "threads");
    messages = db_get_chat_by_id(messages, location->thread_uuid);
    messages = json_object_get_object(messages, "messages");
    uuid_generate_random(message->msg_uuid);
    uuid_unparse_lower(message->msg_uuid, uuid_msg);
    msg = db_create_message(message);
    if (!messages || !msg || json_object_put_object(messages, uuid_msg, msg)) {
        json_object_destroy(msg);
        return false;
    }
    return true;
}