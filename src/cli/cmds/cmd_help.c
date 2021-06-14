/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** help_cmd
*/

#include <stdio.h>

#include "cli/help_string.h"
#include "cli/cli_cmds.h"

void cmd_help(teams_cli_t *cli, char *const *args)
{
    UNUSED(args);
    UNUSED(cli);
    printf("%s\n", HELP_STRING);
}