/*
** EPITECH PROJECT, 2020
** JSON
** File description:
** Json header
*/

#ifndef JSON_H_
#define JSON_H_

#include <stdbool.h>
#include <stdint.h>

//////////////////////// VAR ////////////////////////

// def struct
typedef struct list_s list_t;
typedef struct list_it_s list_it_t;

typedef struct json_element_s json_element_t;

typedef struct json_obj_arr_s json_obj_arr_t;
typedef json_obj_arr_t json_array_t;
typedef json_obj_arr_t json_object_t;

typedef list_it_t json_it_t;

// enum
enum json_type {
    j_null,
    j_array,
    j_object,
    j_bool,
    j_number,
    j_string,
    j_unexist
};

// struct
struct json_obj_arr_s {
    int elements_count;
    list_t *elements;
};

#define JSON_ARRAY_ITERATE(iterator, id, json_obj_arr)                         \
    size_t id = 0;                                                             \
    for (json_it_t *iterator = json_get_it(json_obj_arr); iterator;            \
        json_next_it(&iterator), id++)

#define JSON_OBJECT_ITERATE(iterator, json_obj_arr)                            \
    for (json_it_t *iterator = json_get_it(json_obj_arr); iterator;            \
        json_next_it(&iterator))

///////////////////// PROTOTYPE /////////////////////

// in general, return EXIT_SUCCESS (0) means everythings is good
// and return EXIT_FAILURE (1) means a error happended

// json_array
json_array_t *json_array_create(void);
json_array_t *json_array_clone(json_array_t *ja);
json_array_t *json_array_create_from_string(const char *str);
json_array_t *json_array_create_from_file(const char *path);
char *json_array_to_string(json_array_t *ja);
int json_array_save_to_file(json_array_t *ja, const char *path);
void *json_array_destroy(json_array_t *ja);

// json_array_remove
int json_array_remove(json_array_t *ja, int id);

// json_array_get
int json_array_is_null(json_array_t *ja, int id);
int json_array_get_size(json_array_t *ja);
enum json_type json_array_get_type(json_array_t *ja, int id);
json_array_t *json_array_get_array(json_array_t *ja, int id);
json_object_t *json_array_get_object(json_array_t *ja, int id);
int json_array_get_bool(json_array_t *ja, int id);
int32_t json_array_get_int(json_array_t *ja, int id);
int64_t json_array_get_long(json_array_t *ja, int id);
char *json_array_get_string(json_array_t *ja, int id);

// json_array_put
int json_array_put_null(json_array_t *ja);
int json_array_put_null_at(json_array_t *ja, int id);
int json_array_put_array(json_array_t *ja, json_array_t *value);
int json_array_put_array_at(json_array_t *ja, json_array_t *value, int id);
int json_array_put_object(json_array_t *ja, json_object_t *value);
int json_array_put_object_at(json_array_t *ja, json_object_t *value, int id);
int json_array_put_bool(json_array_t *ja, int value);
int json_array_put_bool_at(json_array_t *ja, int value, int id);
int json_array_put_int(json_array_t *ja, int32_t value);
int json_array_put_int_at(json_array_t *ja, int32_t value, int id);
int json_array_put_long(json_array_t *ja, int64_t value);
int json_array_put_long_at(json_array_t *ja, int64_t value, int id);
int json_array_put_string(json_array_t *ja, const char *value);
int json_array_put_string_at(json_array_t *ja, const char *value, int id);

// json_object
json_object_t *json_object_create(void);
json_object_t *json_object_create_from_string(const char *str);
json_object_t *json_object_create_from_file(const char *path);
json_object_t *json_object_clone(json_object_t *jo);
char *json_object_to_string(json_object_t *jo);
int json_object_save_to_file(json_object_t *jo, const char *path);
void *json_object_destroy(json_object_t *jo);

// json_object_remove
int json_object_remove(json_object_t *jo, const char *key);

// json_object_get
int json_object_has(json_object_t *jo, const char *key);
int json_object_is_null(json_object_t *jo, const char *key);
int json_object_get_size(json_object_t *jo);
enum json_type json_object_get_type(json_object_t *jo, const char *key);
json_array_t *json_object_get_array(json_object_t *jo, const char *key);
json_object_t *json_object_get_object(json_object_t *jo, const char *key);
int json_object_get_bool(json_object_t *jo, const char *key);
int32_t json_object_get_int(json_object_t *jo, const char *key);
int64_t json_object_get_long(json_object_t *jo, const char *key);
char *json_object_get_string(json_object_t *jo, const char *key);

// json_object_put
int json_object_put_null(json_object_t *jo, const char *key);
int json_object_put_array(
    json_object_t *jo, const char *key, json_array_t *value);
int json_object_put_object(
    json_object_t *jo, const char *key, json_object_t *value);
int json_object_put_bool(json_object_t *jo, const char *key, int value);
int json_object_put_int(json_object_t *jo, const char *key, int32_t value);
int json_object_put_long(json_object_t *jo, const char *key, int64_t value);
int json_object_put_string(
    json_object_t *jo, const char *key, const char *value);

// iterator
json_it_t *json_get_it(json_obj_arr_t *json_obj_arr);
bool json_next_it(json_it_t **json_it);

char *json_it_get_key(json_it_t *it);
bool json_it_is_null(json_it_t *it);
enum json_type json_it_get_type(json_it_t *it);
json_array_t *json_it_get_array(json_it_t *it);
json_object_t *json_it_get_object(json_it_t *it);
bool json_it_get_bool(json_it_t *it);
int32_t json_it_get_int(json_it_t *it);
int64_t json_it_get_long(json_it_t *it);
char *json_it_get_string(json_it_t *it);

#endif /* !JSON_H_ */