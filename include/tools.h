/*
** EPITECH PROJECT, 2021
** TOOLS
** File description:
** Tools header
*/

#ifndef TOOLS_H_
#define TOOLS_H_

#include <stdbool.h>
#include <stddef.h>
#include <uuid/uuid.h>

#include "teams.h"

#define UNUSED(x) (void) (x)

// uuid
bool is_valid_str_uuid(const char str_uuid[UUID_STR_LEN]);
void copy_uuid(uuid_t uuid_dest, const uuid_t uuid_src);

// extract data from packet
void exctract_string_from_packet(char *dest, const void *src, size_t src_len);
void exctract_name_from_packet(name_t dest, const void *src);
void exctract_desc_from_packet(desc_t dest, const void *src);
void exctract_body_from_packet(body_t dest, const void *src);

// insert data in packet
void insert_string_in_packet(void *dest, const char *src, size_t dest_len);
void insert_name_in_packet(void *dest, const name_t src);
void insert_desc_in_packet(void *dest, const desc_t src);
void insert_body_in_packet(void *dest, const body_t src);

// str2d
size_t str2d_len(char *const *array);
char **str2d_append(char **array, const char *str);
void *str2d_free(char **array);

// other
bool super_atoi(const char *str, int *value);

bool has_help(const char *const *tab);

void signal_handler(int signal);

void copy_uuid(uuid_t uuid_dest, const uuid_t uuid_src);

#endif /* !TOOLS_H_ */