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

#include "server/server_core.h"
#include "server/teams_server.h"

static void wrong_usage(const char *str, ...)
{
    va_list args;

    printf("myteams_server: ");
    va_start(args, str);
    vprintf(str, args);
    va_end(args);
    printf("\nTry './myteams_server --help' for more information.\n");
}

int main(int argc, const char *const *argv)
{
    int port;

    if (has_help(argv)) {
        printf(TEAMS_SERVER_HELP);
        return EXIT_SUCCESS;
    }
    if (argc != 2) {
        wrong_usage("invalid number of arguments: got %d expected 1", argc - 1);
        return 84;
    }
    if (!super_atoi(argv[1], &port)) {
        wrong_usage("invalid port: '%s'", argv[1]);
        return 84;
    }
    signal(SIGINT, signal_handler);
    signal(SIGPIPE, signal_handler);
    signal(SIGTERM, signal_handler);
    return run_teams_server(port);
}