/*
** EPITECH PROJECT, 2020
** JSON_OBJECT_HAS
** File description:
** Json_object_has function
*/

#include <stddef.h>
#include <stdlib.h>
#include "private_json.h"
#include "json.h"

int json_object_has(json_object_t *jo, const char *key)
{
    if (json_object_get_element(jo, key))
        return (1);
    return (0);
}