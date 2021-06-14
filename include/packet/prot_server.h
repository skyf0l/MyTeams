/*
** EPITECH PROJECT, 2021
** my_teams_rfc
** File description:
** prot_server
*/

#ifndef PROT_SERVER_H_
    #define PROT_SERVER_H_

    #include <uuid/uuid.h>

    #include "prot_pck.h"

    #define NB_SERVER_PACKET_IDS (15)

    enum serv_pck_id {
        SERV_ID_ERROR = 0,
        SERV_ID_SUCCESS = 1,
        SERV_ID_INFO_USER = 2,
        SERV_ID_STATUS = 3,
        SERV_ID_SUBSCRIPTION = 4,
        SERV_ID_UNSUBSCRIBE = 5,
        SERV_ID_INFO_TEAM = 6,
        SERV_ID_INFO_CHAN = 7,
        SERV_ID_INFO_THREAD = 8,
        SERV_ID_INFO_REPLY = 9,
        SERV_ID_INFO_MESSAGE = 10,
        SERV_ID_LIST_HEADER = 11,
        SERV_ID_SET_ENCRYPTION = 12,
        SERV_ID_NOTIFICATION = 13,
        SERV_ID_UUID_NOT_FOUND = 14,
    } __attribute__ ((__packed__));

    enum serv_pck_error_code {
        ERR_INTERNAL = 0,
        ERR_NOT_FOUND = 1,
        ERR_NO_PERM = 2,
        ERR_EMPTY_FIELD = 3,
        ERR_NOT_IMPLEMENTED = 4,
        ERR_ALREADY_EXIST = 5,
    } __attribute__ ((__packed__));

    struct serv_pck_error {
        struct pck pck;
        enum serv_pck_error_code error_code;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct serv_pck_success {
        struct pck pck;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct serv_pck_info_user {
        struct pck pck;
        uuid_t user_uuid;
        char username[MAX_NAME_LENGTH];
        uint8_t status;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct serv_pck_status {
        struct pck pck;
        char version[64];
        uint64_t uptime;
        uint64_t clients_connected;
        uint64_t max_clients;
        char motd[1024];
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct serv_pck_subscription {
        struct pck pck;
        uuid_t user_uuid;
        uuid_t team_uuid;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct serv_pck_unsubscribe {
        struct pck pck;
        uuid_t user_uuid;
        uuid_t team_uuid;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct serv_pck_info_team {
        struct pck pck;
        uuid_t team_uuid;
        char team_name[MAX_NAME_LENGTH];
        char team_desc[MAX_DESCRIPTION_LENGTH];
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct serv_pck_info_chan {
        struct pck pck;
        uuid_t chan_uuid;
        char chan_name[MAX_NAME_LENGTH];
        char chan_desc[MAX_DESCRIPTION_LENGTH];
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct serv_pck_info_thread {
        struct pck pck;
        uuid_t thread_uuid;
        uuid_t user_uuid;
        time_t thread_timestamp;
        char thread_title[MAX_NAME_LENGTH];
        char thread_body[MAX_BODY_LENGTH];
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct serv_pck_info_reply {
        struct pck pck;
        uuid_t team_uuid;
        uuid_t thread_uuid;
        uuid_t sender_uuid;
        time_t reply_timestamp;
        char reply_msg[MAX_BODY_LENGTH];
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct serv_pck_info_msg {
        struct pck pck;
        uuid_t sender_uuid;
        time_t msg_timestamp;
        char msg[MAX_BODY_LENGTH];
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct serv_pck_list_header {
        struct pck pck;
        uint16_t nb_expected_pck;
        uint8_t expected_serv_pck_id;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct serv_pck_set_aes_encryption {
        struct pck pck;
        uint32_t key_length;
        uint8_t key[512];
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    struct serv_pck_notification {
        struct pck pck;
        uint8_t expected_serv_pck_id;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

    enum serv_pck_uuid_not_found_type {
        USER_NOT_FOUND = 0,
        TEAM_NOT_FOUND = 1,
        CHAN_NOT_FOUND = 2,
        THREAD_NOT_FOUND = 3,
    } __attribute__ ((__packed__));

    struct serv_pck_uuid_not_found {
        struct pck pck;
        enum serv_pck_uuid_not_found_type type;
        uuid_t uuid;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

#endif /* !PROT_SERVER_H_ */
