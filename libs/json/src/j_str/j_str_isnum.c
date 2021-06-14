/*
** EPITECH PROJECT, 2020
** J_STR_ISNUM
** File description:
** J_str_isnum function
*/

#include <stddef.h>
#include "private_json.h"

int j_str_isnum(char *str)
{
    if (!str || !*str)
        return (0);
    if ((*str == '-' && j_strlen(str) > LONG_MAX_STR_LEN + 1)
        || (*str != '-' && j_strlen(str) > LONG_MAX_STR_LEN))
        return (0);
    for (int k = (*str == '-'); str[k]; k++)
        if (str[k] < '0' || str[k] > '9')
            return (0);
    if ((*str == '-' && j_strlen(str) < LONG_MAX_STR_LEN)
        || (*str != '-' && j_strlen(str) < LONG_MAX_STR_LEN - 1))
        return (1);
    if (*str == '-' && j_strcmp(&str[1], &LONG_MAX_STR[1]) > 0)
        return (0);
    else if (*str != '-' && j_strcmp(str, LONG_MAX_STR) > 0)
        return (0);
    return (1);
}