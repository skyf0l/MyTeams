/*
** EPITECH PROJECT, 2021
** READ_FILE
** File description:
** Read_file function
*/

#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>

char *add_to_content(char *content, char *add, int add_size)
{
    int k = 0;
    char *new;
    int size = 0;

    if (!add)
        return (content);
    if (content)
        size += strlen(content);
    size += add_size;
    new = malloc(sizeof(char) * (size + 1));
    if (content)
        for (; content[k]; k++)
            new[k] = content[k];
    for (int i = 0; i < add_size; i++, k++)
        new[k] = add[i];
    new[size] = '\0';
    if (content)
        free(content);
    return (new);
}

char *read_file(const char *path)
{
    FILE *file = fopen(path, "r");
    char *line_buff = NULL;
    char *content = NULL;
    size_t line_buff_size = 0;
    int line_size;

    if (!file)
        return (NULL);
    do {
        line_size = getline(&line_buff, &line_buff_size, file);
        if (line_size >= 0)
            content = add_to_content(content, line_buff, line_size);
    }
    while (line_size >= 0);
    free(line_buff);
    fclose(file);
    return (content);
}