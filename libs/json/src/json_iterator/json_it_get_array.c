/*
** EPITECH PROJECT, 2021
** JSON_IT_GET_ARRAY
** File description:
** Json_it_get_array function
*/

#include <stdlib.h>

#include "json.h"
#include "private_json.h"

json_array_t *json_it_get_array(json_it_t *it)
{
    json_element_t *je;

    if (!it)
        return NULL;
    je = (json_element_t *) it->data;
    return je->json_array;
}