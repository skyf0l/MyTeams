/*
** EPITECH PROJECT, 2021
** CLI_FLUSH_SOCKET
** File description:
** Cli_flush_socket function
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>

#include "net/gns/get_next_line.h"
#include "net/gns/get_next_packet.h"

#include "tools.h"

#include "cli/teams_cli.h"

int cli_send_packet(teams_cli_t *cli, const void *raw_packet)
{
    const struct pck *packet = (const struct pck *) raw_packet;

    FD_SET(cli->socket, &cli->io.need_write_fds);
    list_add(cli->last_commands, (void *) (uintptr_t) packet->id);
    return net_buffer_push(&cli->io.write_buffer, raw_packet,
        packet->payload_length + sizeof(struct pck));
}

int cli_flush_socket(teams_cli_t *cli)
{
    int flushed = net_buffer_flush(&cli->io.write_buffer, cli->socket);

    if (flushed == -1 || cli->io.write_buffer.length == 0)
        FD_CLR(cli->socket, &cli->io.need_write_fds);
    return flushed;
}