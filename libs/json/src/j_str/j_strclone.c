/*
** EPITECH PROJECT, 2020
** J_STRCLONE
** File description:
** J_strclone function
*/

#include <stddef.h>
#include <stdlib.h>
#include "private_json.h"

char *j_strclone(const char *str)
{
    char *clone = NULL;
    size_t size = j_strlen(str) + 1;
    size_t k = 0;

    if (!str)
        return (NULL);
    clone = malloc(sizeof(char) * size);
    if (!clone)
        return (NULL);
    for (; str[k]; k++)
        clone[k] = str[k];
    clone[k] = '\0';
    return (clone);
}