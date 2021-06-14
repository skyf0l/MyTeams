/*
** EPITECH PROJECT, 2021
** EXTRACT_STRING_FROM_PACKET
** File description:
** Extract_string_from_packet function
*/

#include <stdlib.h>

#include "teams.h"

void exctract_string_from_packet(char *dest, const void *src, size_t src_len)
{
    const char *src_str = (const char *) src;

    for (size_t k = 0; k < src_len; k++) {
        dest[k] = src_str[k];
        if (dest[k] == 0)
            return;
    }
    dest[src_len] = '\0';
}

void exctract_name_from_packet(name_t dest, const void *src)
{
    exctract_string_from_packet(dest, src, MAX_NAME_LENGTH);
}

void exctract_desc_from_packet(desc_t dest, const void *src)
{
    exctract_string_from_packet(dest, src, MAX_DESCRIPTION_LENGTH);
}

void exctract_body_from_packet(body_t dest, const void *src)
{
    exctract_string_from_packet(dest, src, MAX_BODY_LENGTH);
}