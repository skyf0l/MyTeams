/*
** EPITECH PROJECT, 2021
** DISPLAY_ERROR
** File description:
** Display_error function
*/

#include <stdio.h>

int print_cmd_error(const char *msg)
{
    return printf("Command error: %s\n", msg);
}