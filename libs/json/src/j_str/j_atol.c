/*
** EPITECH PROJECT, 2020
** J_ATOL
** File description:
** J_atol function
*/

#include <stdint.h>

int64_t j_atol(char *str)
{
    int64_t number = 0;
    int is_neg = str[0] == '-';
    int i = str[0] == '-';

    for (; str[i] >= '0' && str[i] <= '9'; i++) {
        number *= 10;
        if (is_neg)
            number -= str[i] - 48;
        else
            number += str[i] - 48;
    }
    return (number);
}