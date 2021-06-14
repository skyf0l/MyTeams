/*
** EPITECH PROJECT, 2021
** JSON_IT_IS_NULL
** File description:
** Json_it_is_null function
*/

#include <stdlib.h>

#include "json.h"
#include "private_json.h"

bool json_it_is_null(json_it_t *it)
{
    json_element_t *je;

    if (!it)
        return false;
    je = (json_element_t *) it->data;
    if (!je || je->type == j_null)
        return true;
    return false;
}