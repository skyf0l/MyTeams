/*
** EPITECH PROJECT, 2021
** JSON_IT_GET_BOOL
** File description:
** Json_it_get_bool function
*/

#include <stdlib.h>

#include "json.h"
#include "private_json.h"

bool json_it_get_bool(json_it_t *it)
{
    json_element_t *je;

    if (!it)
        return false;
    je = (json_element_t *) it->data;
    return !!je->json_number;
}