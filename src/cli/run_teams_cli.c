/*
** EPITECH PROJECT, 2021
** RUN_TEAMS_CLI
** File description:
** Run_teams_cli function
*/

#include <stdio.h>
#include <stdlib.h>

#include "cli/teams_cli.h"

int run_teams_cli(const char *ip, uint16_t port)
{
    teams_cli_t *teams_cli = teams_cli_create(ip, port);

    if (!teams_cli)
        return EXIT_FAILURE;
    cli_loop(teams_cli);
    teams_cli_destroy(teams_cli);
    return EXIT_SUCCESS;
}