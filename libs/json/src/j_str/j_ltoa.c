/*
** EPITECH PROJECT, 2020
** J_LTOA
** File description:
** J_ltoa function
*/

#include <stddef.h>
#include <stdlib.h>
#include "private_json.h"

char *j_ltoa(int64_t n)
{
    char *str = malloc(sizeof(char) * (1 + LONG_MAX_STR_LEN + 1));
    int is_negative = n < 0;
    int64_t rem;
    int k = 0;

    if (n == 0) {
        str[0] = '0';
        str[1] = '\0';
        return (str);
    }
    while (n != 0) {
        rem = n % 10;
        str[k++] = '0' + (rem < 0 ? -rem : rem);
        n /= 10;
    }
    if (is_negative)
        str[k++] = '-';
    str[k] = '\0';
    return (j_strrev(str));
}