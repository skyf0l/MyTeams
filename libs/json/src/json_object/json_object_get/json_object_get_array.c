/*
** EPITECH PROJECT, 2020
** JSON_OBJECT_GET_ARRAY
** File description:
** Json_object_get_array function
*/

#include <stddef.h>
#include <stdlib.h>
#include "private_json.h"
#include "json.h"

json_array_t *json_object_get_array(json_object_t *jo, const char *key)
{
    json_element_t *je = json_object_get_element(jo, key);

    if (je)
        return (je->json_array);
    return (NULL);
}