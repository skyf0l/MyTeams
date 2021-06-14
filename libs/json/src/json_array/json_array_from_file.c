/*
** EPITECH PROJECT, 2020
** JSON_ARRAY_FROM_FILE
** File description:
** Json_array_from_file function
*/

#include <stddef.h>
#include <stdlib.h>
#include "list.h"
#include "private_json.h"
#include "json.h"

char *read_file(const char *path);

json_array_t *json_array_create_from_file(const char *path)
{
    json_array_t *jo;
    char *data;

    if (!(data = read_file(path)))
        return (NULL);
    jo = json_array_create_from_string(data);
    free(data);
    if (!jo)
        return (NULL);
    return (jo);
}