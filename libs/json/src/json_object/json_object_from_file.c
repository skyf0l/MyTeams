/*
** EPITECH PROJECT, 2020
** JSON_OBJECT_FROM_FILE
** File description:
** Json_object_from_file function
*/

#include <stddef.h>
#include <stdlib.h>
#include "list.h"
#include "private_json.h"
#include "json.h"

char *read_file(const char *path);

json_object_t *json_object_create_from_file(const char *path)
{
    json_object_t *jo;
    char *data;

    if (!(data = read_file(path)))
        return (NULL);
    jo = json_object_create_from_string(data);
    free(data);
    if (!jo)
        return (NULL);
    return (jo);
}