/*
** EPITECH PROJECT, 2020
** JSON_ELEMENT_CREATE_INT
** File description:
** Json_element_create_int function
*/

#include <stddef.h>
#include <stdlib.h>
#include "private_json.h"
#include "json.h"

json_element_t *json_element_create_int(const char *key, int32_t value)
{
    json_element_t *je = json_element_create(key);

    if (!je)
        return (NULL);
    je->type = j_number;
    je->json_number = value;
    return (je);
}