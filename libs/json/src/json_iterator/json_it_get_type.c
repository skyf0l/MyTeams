/*
** EPITECH PROJECT, 2021
** JSON_IT_GET_TYPE
** File description:
** Json_it_get_type function
*/

#include <stdlib.h>

#include "json.h"
#include "private_json.h"

enum json_type json_it_get_type(json_it_t *it)
{
    json_element_t *je;

    if (!it)
        return j_null;
    je = (json_element_t *) it->data;
    return je->type;
}