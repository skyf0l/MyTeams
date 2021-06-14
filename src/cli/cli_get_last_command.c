/*
** EPITECH PROJECT, 2021
** CLI_GET_LAST_COMMAND
** File description:
** Cli_get_last_command function
*/

#include "cli/teams_cli.h"

enum cli_pck_id cli_get_last_command(teams_cli_t *cli)
{
    return (enum cli_pck_id) list_pop(cli->last_commands, 0);
}
