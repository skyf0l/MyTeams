/*
** EPITECH PROJECT, 2021
** JSON_ITERATOR
** File description:
** Json_iterator function
*/

#include <stddef.h>

#include "json.h"
#include "list.h"

json_it_t *json_get_it(json_obj_arr_t *json_obj_arr)
{
    if (!json_obj_arr)
        return NULL;
    return list_get_it(json_obj_arr->elements);
}

bool json_next_it(json_it_t **json_it)
{
    return next_it(json_it);
}