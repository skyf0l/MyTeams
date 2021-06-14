/*
** EPITECH PROJECT, 2021
** INSERT_STRING_IN_PACKET
** File description:
** Insert_string_in_packet function
*/

#include <stdlib.h>

#include "teams.h"

void insert_string_in_packet(void *dest, const char *src, size_t dest_len)
{
    size_t k;

    for (k = 0; k < dest_len && src[k]; k++)
        ((char *) dest)[k] = src[k];
    if (k < dest_len && ((char *) dest)[k] != '\0')
        for (; k < dest_len; k++)
            ((char *) dest)[k] = '\0';
}

void insert_name_in_packet(void *dest, const name_t src)
{
    insert_string_in_packet(dest, src, MAX_NAME_LENGTH);
}

void insert_desc_in_packet(void *dest, const desc_t src)
{
    insert_string_in_packet(dest, src, MAX_DESCRIPTION_LENGTH);
}

void insert_body_in_packet(void *dest, const body_t src)
{
    insert_string_in_packet(dest, src, MAX_BODY_LENGTH);
}