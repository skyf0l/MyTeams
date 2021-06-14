/*
** EPITECH PROJECT, 2021
** CMD_REPLY_SET_AES_ENCRYPTION
** File description:
** Cmd_reply_set_aes_encryption function
*/

#include <stdio.h>

#include "tools.h"

#include "packet/prot_server.h"

#include "cli/teams_cli.h"

void cmd_reply_set_aes_encryption(
    teams_cli_t *cli, const struct serv_pck_set_aes_encryption *packet)
{
    enum cli_pck_id last_command = cli_get_last_command(cli);

    UNUSED(last_command), UNUSED(packet);
    printf("Receive packet set_aes_encryption\n");
}