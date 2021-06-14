/*
** EPITECH PROJECT, 2021
** JSON_IT_GET_LONG
** File description:
** Json_it_get_long function
*/

#include <stdlib.h>

#include "json.h"
#include "private_json.h"

int64_t json_it_get_long(json_it_t *it)
{
    json_element_t *je;

    if (!it)
        return 0;
    je = (json_element_t *) it->data;
    return je->json_number;
}