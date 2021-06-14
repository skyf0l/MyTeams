/*
** EPITECH PROJECT, 2020
** J_STRCMP
** File description:
** J_strcmp function
*/

#include <stddef.h>

int j_strcmp(const char *s1, const char *s2)
{
    int c;

    if (!s1 || !s2)
        return (-1);
    for (c = 0; s1[c] == s2[c]; c++) {
        if (s1[c] == '\0' || s2[c] == '\0' )
            return (s1[c] - s2[c]);
    }
    return (s1[c] - s2[c]);
}