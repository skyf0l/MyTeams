/*
** EPITECH PROJECT, 2021
** my_teams_rfc
** File description:
** prot_pck
*/

#ifndef PROT_PCK_H_
    #define PROT_PCK_H_

    #include <stdint.h>

    #ifndef MAX_NAME_LENGTH
        #define MAX_NAME_LENGTH (32)
    #endif /* !MAX_NAME_LENGTH */
    #ifndef MAX_DESCRIPTION_LENGTH
        #define MAX_DESCRIPTION_LENGTH (255)
    #endif /* !MAX_DESCRIPTION_LENGTH */
    #ifndef MAX_BODY_LENGTH
        #define MAX_BODY_LENGTH (512)
    #endif /* !MAX_BODY_LENGTH */

    #ifndef PACKET_ENDIANNESS
        #define PACKET_ENDIANNESS "little-endian"
    #endif /* !PACKET_ENDIANNESS */

    #define PCK_LENGTH(pck_name) (sizeof(pck_name) - sizeof(struct pck))

    struct pck {
        uint16_t payload_length;
        uint8_t id;
    } __attribute__ ((__packed__, scalar_storage_order(PACKET_ENDIANNESS)));

#endif /* !PROT_PCK_H_ */
