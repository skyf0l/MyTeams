/*
** EPITECH PROJECT, 2021
** my_teams_rfc
** File description:
** prot_client
*/

#ifndef PROT_CLIENT_H_
    #define PROT_CLIENT_H_

    #include <uuid/uuid.h>

    #include "prot_pck.h"

    #define NB_CLIENT_PACKET_IDS (25)

    enum cli_pck_id {
        CLI_ID_LOGIN = 0,
        CLI_ID_DISCONNECT = 1,
        CLI_ID_USERS = 2,
        CLI_ID_USER = 3,
        CLI_ID_SEND = 4,
        CLI_ID_MESSAGES = 5,
        CLI_ID_SUB_TEAM = 6,
        CLI_ID_SUB_USR_TEAM = 7,
        CLI_ID_SUB_LIST_TEAMS = 8,
        CLI_ID_UNSUB_TEAM = 9,
        CLI_ID_CREATE_TEAM = 10,
        CLI_ID_CREATE_CHAN = 11,
        CLI_ID_CREATE_THREAD = 12,
        CLI_ID_CREATE_REPLY = 13,
        CLI_ID_LIST_TEAMS = 14,
        CLI_ID_LIST_CHANS = 15,
        CLI_ID_LIST_THREADS = 16,
        CLI_ID_LIST_REPLIES = 17,
        CLI_ID_INFO_USR = 18,
        CLI_ID_INFO_TEAM = 19,
        CLI_ID_INFO_CHAN = 20,
        CLI_ID_INFO_THREAD = 21,
        CLI_ID_PING = 22,
        CLI_ID_SET_COMP = 23,
        CLI_ID_SET_ENC = 24,
        CLI_ID_NOTIFICATION = 25,
    } __attribute__ ((__packed__));

    struct cli_pck_login {
        struct pck pck;
        char username[MAX_NAME_LENGTH];
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_disconnect {
        struct pck pck;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_users {
        struct pck pck;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_user {
        struct pck pck;
        uuid_t user_uuid;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_send {
        struct pck pck;
        uuid_t user_uuid;
        char msg[MAX_BODY_LENGTH];
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_messages {
        struct pck pck;
        uuid_t user_uuid;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_sub_team {
        struct pck pck;
        uuid_t team_uuid;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_sub_usr_team {
        struct pck pck;
        uuid_t team_uuid;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_sub_list_teams {
        struct pck pck;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_unsub_team {
        struct pck pck;
        uuid_t team_uuid;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_create_team {
        struct pck pck;
        char team_name[MAX_NAME_LENGTH];
        char team_desc[MAX_DESCRIPTION_LENGTH];
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_create_chan {
        struct pck pck;
        uuid_t team_uuid;
        char chan_name[MAX_NAME_LENGTH];
        char chan_description[MAX_DESCRIPTION_LENGTH];
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_create_thread {
        struct pck pck;
        uuid_t team_uuid;
        uuid_t chan_uuid;
        char thread_title[MAX_NAME_LENGTH];
        char thread_message[MAX_BODY_LENGTH];
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_create_reply {
        struct pck pck;
        uuid_t team_uuid;
        uuid_t chan_uuid;
        uuid_t thread_uuid;
        char reply_msg[MAX_BODY_LENGTH];
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_list_teams {
        struct pck pck;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_list_chans {
        struct pck pck;
        uuid_t team_uuid;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_list_threads {
        struct pck pck;
        uuid_t team_uuid;
        uuid_t chan_uuid;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_list_replies {
        struct pck pck;
        uuid_t team_uuid;
        uuid_t chan_uuid;
        uuid_t thread_uuid;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_info_usr {
        struct pck pck;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_info_team {
        struct pck pck;
        uuid_t team_uuid;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_info_chan {
        struct pck pck;
        uuid_t team_uuid;
        uuid_t chan_uuid;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_info_thread {
        struct pck pck;
        uuid_t team_uuid;
        uuid_t chan_uuid;
        uuid_t thread_uuid;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct cli_pck_ping {
        struct pck pck;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    enum cli_pck_compression_type {
        NO_COMP = 0
    } __attribute__ ((__packed__));

    struct cli_pck_set_comp {
        struct pck pck;
        enum cli_pck_compression_type comp_type;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    enum cli_pck_encryption_type {
        NO_ENC = 0,
        AES_ECB = 1,
        AES_CBC = 2
    } __attribute__ ((__packed__));

    struct cli_pck_set_enc {
        struct pck pck;
        enum cli_pck_encryption_type enc_type;
        uint32_t key_length;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

#endif /* !PROT_CLIENT_H_ */
