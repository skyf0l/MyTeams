/*
** EPITECH PROJECT, 2020
** JSON_ARRAY_GET_INT
** File description:
** Json_array_get_int function
*/

#include <stddef.h>
#include <stdlib.h>
#include "private_json.h"
#include "json.h"

int32_t json_array_get_int(json_array_t *ja, int id)
{
    json_element_t *je = json_array_get_element(ja, id);

    if (je)
        return ((int32_t) je->json_number);
    return (0);
}