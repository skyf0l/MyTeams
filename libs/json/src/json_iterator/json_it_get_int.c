/*
** EPITECH PROJECT, 2021
** JSON_IT_GET_INT
** File description:
** Json_it_get_int function
*/

#include <stdlib.h>

#include "json.h"
#include "private_json.h"

int32_t json_it_get_int(json_it_t *it)
{
    json_element_t *je;

    if (!it)
        return 0;
    je = (json_element_t *) it->data;
    return (int32_t) je->json_number;
}