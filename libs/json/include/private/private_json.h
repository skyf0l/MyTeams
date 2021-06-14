/*
** EPITECH PROJECT, 2020
** PRIVATE_JSON
** File description:
** Private_json header
*/

#ifndef PRIVATE_JSON_H_
#define PRIVATE_JSON_H_

#include <stdint.h>

#include "json.h"
#include "list.h"

//////////////////////// VAR ////////////////////////

// const
static const char ESCAPE_CHARS[8] = "\b\f\n\r\t\"\\";
static const char UNESCAPE_CHARS[8] = "bfnrt\"\\";
static const char WHITE_SPACES[5] = " \n\r\t";

// struct
struct json_element_s
{
    enum json_type type;
    char *key;
    json_array_t *json_array;
    json_object_t *json_object;
    int64_t json_number;
    char *json_string;
};

///////////////////// PROTOTYPE /////////////////////

// json_array and json_object recursive from_string
json_array_t *ja_create_from_string(char **str);
json_element_t *json_parser_to_element_array(char *key, char **str);
json_element_t *json_parser_to_element_object(char *key, char **str);

// json_array_get
json_element_t *json_array_get_element(json_array_t *ja, int id);

// json_object_get
json_element_t *json_object_get_element(json_object_t *jo, const char *key);

// json_element
json_element_t *json_element_create(const char *key);
json_element_t *json_element_clone(json_element_t *je);
json_element_t *json_element_create_array(const char *key, json_array_t *value);
json_element_t *json_element_create_object(const char *key,
    json_object_t *value);
json_element_t *json_element_create_bool(const char *key, int value);
json_element_t *json_element_create_int(const char *key, int32_t value);
json_element_t *json_element_create_long(const char *key, int64_t value);
json_element_t *json_element_create_string(const char *key, const char *value);
void *json_element_destroy(json_element_t *je);
void json_element_destroy_no_rtn(json_element_t *je);

// json_to_string
char *json_element_to_string(json_element_t *je);
char *json_key_to_string(char *key);
int json_to_string_append(char **str, const char *to_add);

// json_string
char js_to_escape_char(char c);
char js_to_unescape_char(char c);
int js_is_unescape_char(char c);
int js_is_escape_char(char c);
int js_count_special_chars(char *str);
char *get_string_from_json_format(char *str);
char *get_string_to_json_format(char *str);

// json_parser
json_object_t *jo_create_from_string(char **str);
int sp_is_white_space(char c);
void json_parser_skip_white_spaces(char **str);
char *json_parser_get_string(char **str);
int jp_get_string_size(char *str);
char *json_parser_get_value_string(char **str);
int jp_get_value_string_size(char *str);
enum json_type json_parser_get_value_type(char *type);
json_element_t *json_parser_to_element(enum json_type type,
    char *key, char *value);
json_element_t *json_parser_to_array_element(char **str);
json_element_t *json_parser_to_object_element(char **str);

// j_str

static const size_t LONG_MAX_STR_LEN = 19;
static const char LONG_MIN_STR[] = "-9223372036854775808";
static const char LONG_MAX_STR[] = "9223372036854775807";

size_t j_strlen(const char *str);
char *j_strclone(const char *str);
int j_strcmp(const char *s1, const char *s2);
int j_str_isnum(char *str);
int64_t j_atol(char *str);
char *j_ltoa(int64_t n);
char *j_strrev(char *str);

#endif /* !PRIVATE_JSON_H_ */