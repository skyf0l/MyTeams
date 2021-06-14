/*
** EPITECH PROJECT, 2021
** JSON_ARRAY_SAVE_TO_FILE
** File description:
** Json_array_save_to_file function
*/

#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "json.h"

int json_array_save_to_file(json_array_t *ja, const char *path)
{
    int return_value = EXIT_SUCCESS;
    char *content = json_array_to_string(ja);
    int fd;

    if (!content)
        return EXIT_FAILURE;
    fd = open(path, O_TRUNC | O_WRONLY | O_CREAT, 0644);
    if (fd == -1)
        return EXIT_FAILURE;
    if (write(fd, content, strlen(content)) == -1)
        return_value = EXIT_FAILURE;
    close(fd);
    free(content);
    return return_value;
}