/*
** EPITECH PROJECT, 2021
** PARSE_LINE
** File description:
** Parse_line function
*/

#include <stdio.h>
#include <stdlib.h>

#include "tools.h"

static bool is_empty_line(const char *line)
{
    for (size_t k = 0; line[k]; k++)
        if (line[k] != ' ')
            return false;
    return true;
}

char **parse_cmd(const char *line)
{
    char **args = NULL;
    char buff_arg[1024 + 1] = { 0 };
    int nb_char_extracted = 0;
    int res;

    if (!line)
        return NULL;
    if (is_empty_line(line))
        return str2d_append(args, NULL);
    do {
        nb_char_extracted = 0;
        res = sscanf(line, " \"%1024[^\"]\" %n", buff_arg, &nb_char_extracted);
        if (res <= 0 || nb_char_extracted == 0)
            return str2d_free(args);
        args = str2d_append(args, buff_arg);
        if (!args)
            return NULL;
        line += nb_char_extracted;
    } while (*line);
    return args;
}