/*
** EPITECH PROJECT, 2021
** MAIN
** File description:
** Main function
*/

#include <signal.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "teams.h"
#include "tools.h"

#include "cli/teams_cli.h"

static void wrong_usage(const char *str, ...)
{
    va_list args;

    printf("myteams_cli: ");
    va_start(args, str);
    vprintf(str, args);
    va_end(args);
    printf("\nTry './myteams_cli --help' for more information.\n");
}

int main(int argc, const char *const *argv)
{
    int port;

    if (has_help(argv)) {
        printf(TEAMS_CLI_HELP);
        return EXIT_SUCCESS;
    }
    if (argc != 3) {
        wrong_usage("invalid number of arguments: got %d expected 3", argc);
        return 84;
    }
    if (!super_atoi(argv[2], &port)) {
        wrong_usage("invalid port: '%s'", argv[1]);
        return 84;
    }
    signal(SIGINT, signal_handler);
    signal(SIGPIPE, signal_handler);
    signal(SIGTERM, signal_handler);
    return run_teams_cli(argv[1], (uint16_t) port);
}