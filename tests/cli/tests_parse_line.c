/*
** EPITECH PROJECT, 2021
** TESTS_PARSE_CMD
** File description:
** Test parse_cmd
*/

#include <criterion/criterion.h>

#include "tools.h"

#include "cli/teams_cli.h"

Test(parse_cmd, null)
{
    const char *line = NULL;
    char **args = parse_cmd(line);

    cr_assert_null(args);
    cr_assert_eq(str2d_len(args), 0);
    str2d_free(args);
}

Test(parse_cmd, empty)
{
    const char *line = "";
    char **args = parse_cmd(line);

    cr_assert_not_null(args);
    cr_assert_eq(str2d_len(args), 0);
    str2d_free(args);
}

Test(parse_cmd, space)
{
    const char *line = "   ";
    char **args = parse_cmd(line);

    cr_assert_not_null(args);
    cr_assert_eq(str2d_len(args), 0);
    str2d_free(args);
}

Test(parse_cmd, one_arg_1)
{
    const char *line = "\"arg1\"";
    char **args = parse_cmd(line);

    cr_assert_not_null(args);
    cr_assert_eq(str2d_len(args), 1);
    cr_assert_str_eq(args[0], "arg1");
    cr_assert_null(args[1]);
    str2d_free(args);
}

Test(parse_cmd, one_arg_2)
{
    const char *line = "\" arg 1 \"";
    char **args = parse_cmd(line);

    cr_assert_not_null(args);
    cr_assert_eq(str2d_len(args), 1);
    cr_assert_str_eq(args[0], " arg 1 ");
    cr_assert_null(args[1]);
    str2d_free(args);
}

Test(parse_cmd, one_arg_3)
{
    const char *line = " \" arg 1 \"";
    char **args = parse_cmd(line);

    cr_assert_not_null(args);
    cr_assert_eq(str2d_len(args), 1);
    cr_assert_str_eq(args[0], " arg 1 ");
    cr_assert_null(args[1]);
    str2d_free(args);
}


Test(parse_cmd, two_args_1)
{
    const char *line = "\"arg1\" \"arg2\"";
    char **args = parse_cmd(line);

    cr_assert_not_null(args);
    cr_assert_eq(str2d_len(args), 2);
    cr_assert_str_eq(args[0], "arg1");
    cr_assert_str_eq(args[1], "arg2");
    cr_assert_null(args[2]);
    str2d_free(args);
}

Test(parse_cmd, two_args_2)
{
    const char *line = "\" arg 1 \" \" arg 2 \"";
    char **args = parse_cmd(line);

    cr_assert_not_null(args);
    cr_assert_eq(str2d_len(args), 2);
    cr_assert_str_eq(args[0], " arg 1 ");
    cr_assert_str_eq(args[1], " arg 2 ");
    cr_assert_null(args[2]);
    str2d_free(args);
}

Test(parse_cmd, two_args_multi_spaces)
{
    const char *line = " \"arg1\"     \"arg2\"";
    char **args = parse_cmd(line);

    cr_assert_not_null(args);
    cr_assert_eq(str2d_len(args), 2);
    cr_assert_str_eq(args[0], "arg1");
    cr_assert_str_eq(args[1], "arg2");
    cr_assert_null(args[2]);
    str2d_free(args);
}

Test(parse_cmd, error_1)
{
    const char *line = "arg1";
    char **args = parse_cmd(line);

    cr_assert_null(args);
}

Test(parse_cmd, error_2)
{
    const char *line = "\"arg1";
    char **args = parse_cmd(line);

    cr_assert_null(args);
}

Test(parse_cmd, error_3)
{
    const char *line = "arg1\"";
    char **args = parse_cmd(line);

    cr_assert_null(args);
}

Test(parse_cmd, error_4)
{
    const char *line = "\"arg1\" \"";
    char **args = parse_cmd(line);

    cr_assert_null(args);
}

Test(parse_cmd, error_5)
{
    const char *line = "\"arg1\" \"arg";
    char **args = parse_cmd(line);

    cr_assert_null(args);
}