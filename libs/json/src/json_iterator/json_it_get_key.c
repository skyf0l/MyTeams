/*
** EPITECH PROJECT, 2021
** JSON_IT_GET_KEY
** File description:
** Json_it_get_key function
*/

#include <stdlib.h>

#include "json.h"
#include "private_json.h"

char *json_it_get_key(json_it_t *it)
{
    json_element_t *je;

    if (!it)
        return NULL;
    je = (json_element_t *) it->data;
    return je->key;
}