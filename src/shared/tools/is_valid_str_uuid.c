/*
** EPITECH PROJECT, 2021
** IS_VALID_STR_UUID
** File description:
** Is_valid_str_uuid function
*/

#include <stdbool.h>
#include <uuid/uuid.h>

bool is_valid_str_uuid(const char str_uuid[UUID_STR_LEN])
{
    uuid_t tmp;

    return uuid_parse(str_uuid, tmp) != -1;
}