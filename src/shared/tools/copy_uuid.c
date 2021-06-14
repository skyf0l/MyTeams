/*
** EPITECH PROJECT, 2021
** COPY_UUID
** File description:
** Copy_uuid function
*/

#include <string.h>
#include <uuid/uuid.h>

#include "teams.h"

void copy_uuid(uuid_t uuid_dest, const uuid_t uuid_src)
{
    memcpy(uuid_dest, uuid_src, UUID_LENGTH);
}