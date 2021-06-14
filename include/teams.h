/*
** EPITECH PROJECT, 2021
** TEAMS
** File description:
** Teams header
*/

#ifndef TEAMS_H_
#define TEAMS_H_

#ifndef MAX_NAME_LENGTH
    #define MAX_NAME_LENGTH (32)
#endif /* !MAX_NAME_LENGTH */
#ifndef MAX_DESCRIPTION_LENGTH
    #define MAX_DESCRIPTION_LENGTH (255)
#endif /* !MAX_DESCRIPTION_LENGTH */
#ifndef MAX_BODY_LENGTH
    #define MAX_BODY_LENGTH (512)
#endif /* !MAX_BODY_LENGTH */
#ifndef UUID_LENGTH
    #define UUID_LENGTH (16)
#endif /* !UUID_LENGTH */
#ifndef UUID_STR_LEN
    #define UUID_STR_LEN (36 + 1)
#endif /* !UUID_STR_LEN */

// types
typedef char uuid_str_t[UUID_STR_LEN];
typedef char name_t[MAX_NAME_LENGTH + 1];
typedef char desc_t[MAX_DESCRIPTION_LENGTH + 1];
typedef char body_t[MAX_BODY_LENGTH + 1];

// database
static const char DATABASE_PATH[] = "database.json";
static const char VERSION[] = "1.0 ALPHA";
static const char MOTD[] = "MOTD";

// help
static const char TEAMS_SERVER_HELP[] =
    "USAGE: ./myteams_server port\n"
    "\tport is the port number on which the server socket listens.\n";
static const char TEAMS_CLI_HELP[] =
    "USAGE: ./myteams_cli ip port\n"
    "\tip is the server ip address on which the server socket listens\n"
    "\tport is the port number on which the server socket listens\n";

#endif /* !TEAMS_H_ */