/*
** EPITECH PROJECT, 2021
** JSON_IT_GET_OBJECT
** File description:
** Json_it_get_object function
*/

#include <stdlib.h>

#include "json.h"
#include "private_json.h"

json_object_t *json_it_get_object(json_it_t *it)
{
    json_element_t *je;

    if (!it)
        return NULL;
    je = (json_element_t *) it->data;
    return je->json_object;
}