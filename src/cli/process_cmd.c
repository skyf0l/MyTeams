/*
** EPITECH PROJECT, 2021
** PROCESS_CMDS
** File description:
** Process_cmds function
*/

#include <stdlib.h>
#include <string.h>

#include "tools.h"

#include "cli/cli_cmds.h"
#include "cli/teams_cli.h"

static bool has_good_argument_count(
    const size_t *required_nb_args, char *const *cmd_args)
{
    size_t nb_args = str2d_len(cmd_args);

    for (size_t k = 0; required_nb_args[k] != (size_t) -1; k++)
        if (required_nb_args[k] == nb_args)
            return true;
    return false;
}

void process_cmd(teams_cli_t *cli, const char *line)
{
    char **cmd_args = NULL;

    if (strlen(line) == 0)
        return;
    for (int i = 0; tab[i].str; i++) {
        if (strncmp(line, tab[i].str, strlen(tab[i].str)) != 0)
            continue;
        cmd_args = parse_cmd(line + strlen(tab[i].str));
        if (!cmd_args) {
            print_cmd_error("Invalid arguments");
            return;
        }
        if (has_good_argument_count(tab[i].required_nb_args, cmd_args))
            tab[i].function(cli, cmd_args);
        else
            print_cmd_error("Invalid argument count");
        str2d_free(cmd_args);
        return;
    }
    print_cmd_error("Unknown command");
}