/*
** EPITECH PROJECT, 2021
** CMD_REPLY_LIST_HEADER
** File description:
** Cmd_reply_list_header function
*/

#include <stdio.h>

#include "tools.h"

#include "packet/prot_server.h"

#include "cli/teams_cli.h"

static void print_empty_list(enum cli_pck_id last_command)
{
    if (last_command == CLI_ID_USERS)
        printf("No users found\n");
    if (last_command == CLI_ID_MESSAGES)
        printf("No private messages found\n");
    if (last_command == CLI_ID_LIST_TEAMS)
        printf("No teams found\n");
    if (last_command == CLI_ID_LIST_CHANS)
        printf("No chans found\n");
    if (last_command == CLI_ID_LIST_THREADS)
        printf("No threads found\n");
    if (last_command == CLI_ID_LIST_REPLIES)
        printf("No replies found\n");
    if (last_command == CLI_ID_SUB_LIST_TEAMS)
        printf("No teams subscribed\n");
    if (last_command == CLI_ID_SUB_USR_TEAM)
        printf("No users subscribed to team\n");
}

void cmd_reply_list_header(
    teams_cli_t *cli, const struct serv_pck_list_header *packet)
{
    enum cli_pck_id last_command = cli_get_last_command(cli);

    if (packet->nb_expected_pck == 0)
        print_empty_list(last_command);
    for (size_t k = 0; k < packet->nb_expected_pck; k++)
        list_add_at(cli->last_commands, (void *) (uintptr_t) last_command, 0);
}