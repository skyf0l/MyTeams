/*
** EPITECH PROJECT, 2021
** B-NWP-400-TLS-4-1-myteams-pauline.faure
** File description:
** subscribed_cmd
*/

#include "packet/prot_client.h"

#include "cli/cli_cmds.h"

static void list_all_subscribed_teams(teams_cli_t *cli)
{
    struct cli_pck_sub_list_teams teams_sub = {
        {
            .id = CLI_ID_SUB_LIST_TEAMS,
            .payload_length = PCK_LENGTH(struct cli_pck_sub_list_teams),
        },
    };

    cli_send_packet(cli, &teams_sub);
}

static void list_all_users_subscribed_to_a_team(
    teams_cli_t *cli, char *const *args)
{
    struct cli_pck_sub_usr_team teams_sub_usr = {
        {
            .id = CLI_ID_SUB_USR_TEAM,
            .payload_length = PCK_LENGTH(struct cli_pck_sub_usr_team),
        },
        .team_uuid = { 0 },
    };

    CMD_CHECK_VALID_UUID_STR(args[0]);
    uuid_parse(args[0], teams_sub_usr.team_uuid);
    cli_send_packet(cli, &teams_sub_usr);
}

void cmd_subscribed(teams_cli_t *cli, char *const *args)
{
    if (str2d_len(args) == 0)
        list_all_subscribed_teams(cli);
    else
        list_all_users_subscribed_to_a_team(cli, args);
}