/*
** EPITECH PROJECT, 2020
** JSON_ARRAY_GET_LONG
** File description:
** Json_array_get_long function
*/

#include <stddef.h>
#include <stdlib.h>
#include "private_json.h"
#include "json.h"

int64_t json_array_get_long(json_array_t *ja, int id)
{
    json_element_t *je = json_array_get_element(ja, id);

    if (je)
        return (je->json_number);
    return (0);
}