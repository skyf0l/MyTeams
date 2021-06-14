/*
** EPITECH PROJECT, 2021
** TEAMS_CLI
** File description:
** Teams_cli function
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "net/net_socket.h"

#include "tools.h"

#include "cli/teams_cli.h"

static bool format_ip_address(struct in_addr *sin_addr, const char *ip)
{
    if (strcmp(ip, "localhost") == 0)
        ip = "127.0.0.1";
    if (inet_pton(AF_INET, ip, sin_addr) <= 0) {
        printf("Invalid address\n");
        return false;
    }
    return true;
}

static int connect_socket(const char *ip, uint16_t port)
{
    int sock_fd = 0;
    address_t serv_addr;

    serv_addr.sa_in = (struct sockaddr_in) {
        .sin_family = AF_INET,
        .sin_port = htons(port),
    };

    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        printf("\n Socket creation error \n");
        return -1;
    }
    if (!format_ip_address(&serv_addr.sa_in.sin_addr, ip))
        return -1;
    if (connect(sock_fd, &serv_addr.sa, sizeof(serv_addr)) < 0) {
        printf("Connection failed\n");
        return -1;
    }
    return sock_fd;
}

teams_cli_t *teams_cli_create(const char *ip, uint16_t port)
{
    teams_cli_t *teams_cli = malloc(sizeof(teams_cli_t));

    if (!teams_cli)
        return NULL;
    memset(teams_cli, 0, sizeof(teams_cli_t));
    teams_cli->socket = connect_socket(ip, port);
    if (teams_cli->socket == -1)
        return teams_cli_destroy(teams_cli);
    teams_cli->last_commands = list_create(NULL);
    if (!teams_cli->last_commands)
        return teams_cli_destroy(teams_cli);
    FD_ZERO(&teams_cli->io.need_read_fds);
    FD_ZERO(&teams_cli->io.need_write_fds);
    FD_SET(STD_IN, &teams_cli->io.need_read_fds);
    FD_SET(teams_cli->socket, &teams_cli->io.need_read_fds);
    printf("Connected to server\n");
    return teams_cli;
}

void *teams_cli_destroy(teams_cli_t *teams_cli)
{
    if (!teams_cli)
        return NULL;
    if (teams_cli->socket != -1)
        close(teams_cli->socket);
    if (teams_cli->io.write_buffer.buffer)
        free(teams_cli->io.write_buffer.buffer);
    if (teams_cli->last_commands)
        list_destroy(teams_cli->last_commands);
    free(teams_cli);
    return NULL;
}