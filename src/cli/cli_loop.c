/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** cli_loop
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

#include "net/gns/get_next_line.h"
#include "net/gns/get_next_packet.h"

#include "tools.h"

#include "cli/teams_cli.h"

static void simulate_logout(teams_cli_t *cli)
{
    printf("/logout\n");
    process_cmd(cli, "/logout");
}

static bool get_cmd_loop(teams_cli_t *cli)
{
    int read_size = 0;
    char *line = NULL;

    line = gnl(STD_IN, &read_size);
    if (read_size <= 0 || line == NULL) {
        free(line);
        if (read_size == 0 && *cli->username) {
            simulate_logout(cli);
            return true;
        }
        return (read_size > 0);
    }
    process_cmd(cli, line);
    free(line);
    line = NULL;
    while ((line = gnl_extract_next_line(STD_IN)) != NULL) {
        process_cmd(cli, line);
        free(line);
    }
    return true;
}

static bool get_packet_loop(teams_cli_t *cli)
{
    int read_size = 0;
    struct pck *packet;

    packet = gnp(cli->socket, &read_size);
    if (read_size <= 0 || !packet) {
        free(packet);
        return (read_size > 0);
    }
    process_reply(cli, packet);
    free(packet);
    packet = NULL;
    while ((packet = gnp_extract_next_packet(cli->socket)) != NULL) {
        process_reply(cli, packet);
        free(packet);
    }
    return true;
}

static bool process_fds(teams_cli_t *cli, fd_set *read_fds, fd_set *write_fds)
{
    if (FD_ISSET(STD_IN, read_fds))
        if (!get_cmd_loop(cli))
            return false;
    if (FD_ISSET(cli->socket, read_fds))
        if (!get_packet_loop(cli)) {
            printf("Server closed, exit cli\n");
            return false;
        }
    if (FD_ISSET(cli->socket, write_fds))
        if (cli_flush_socket(cli) == -1)
            return false;
    return true;
}

void cli_loop(teams_cli_t *cli)
{
    fd_set read_fds;
    fd_set write_fds;

    cli->running = true;
    while (cli->running) {
        memcpy(&read_fds, &cli->io.need_read_fds, sizeof(fd_set));
        memcpy(&write_fds, &cli->io.need_write_fds, sizeof(fd_set));
        if (select(FD_SETSIZE, &read_fds, &write_fds, NULL, NULL) == -1) {
            printf("Select failed, exit cli\n");
            break;
        }
        if (!process_fds(cli, &read_fds, &write_fds))
            break;
    }
}