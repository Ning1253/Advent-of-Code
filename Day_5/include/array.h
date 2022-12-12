#ifndef c_array_h
#define c_array_h

#include <stdint.h>
#include <stdlib.h>

#define max(a, b) a >= b ? a : b


#define ARRAY(NAME, TYPE)                                               \
                                                                        \
typedef struct NAME##Array {                                            \
    int64_t size;                                                       \
    int64_t used;                                                       \
    TYPE*  data;                                                        \
} *NAME##Array;                                                         \
                                                                        \
void append##NAME##Array(NAME##Array array, TYPE item) {                \
    if (array->used >= array->size) {                                   \
        if (array->size) {                                              \
            array->data = realloc(                                      \
                array->data, 2 * array->size * sizeof(TYPE)             \
            );                                                          \
            array->size *= 2;                                           \
        } else {                                                        \
            array->data = calloc(8, sizeof(TYPE));                      \
            array->size = 8;                                            \
        }                                                               \
    }                                                                   \
                                                                        \
    array->data[array->used] = item;                                    \
    array->used += 1;                                                   \
}                                                                       \
                                                                        \
void set##NAME##Array(NAME##Array array, TYPE item, int64_t index) {    \
    int size_change = 0;                                                \
                                                                        \
    if (!array->size) {                                                 \
        array->size = 8;                                                \
        size_change = 1;                                                \
    }                                                                   \
                                                                        \
    while (array->size <= index) {                                      \
        array->size *= 2;                                               \
        size_change = 1;                                                \
    }                                                                   \
                                                                        \
    if (size_change) {                                                  \
        array->data = realloc(                                          \
            array->data, array->size * sizeof(TYPE)                     \
        );                                                              \
    }                                                                   \
                                                                        \
    array->data[index] = item;                                          \
                                                                        \
    array->used = max(array->used, index + 1);                          \
}                                                                       \
                                                                        \
TYPE read##NAME##Array(NAME##Array array, int64_t index) {              \
    if (index < array->used && index >= -(array->used))                 \
        return array->data[index + ((index > -1) ? 0 : array->used)];   \
    else {                                                              \
        printf("Error: Index out of bounds. \n");                       \
        exit(1);                                                        \
    }                                                                   \
}                                                                       \
                                                                        \
NAME##Array init##NAME##Array() {                                       \
    return calloc(1, sizeof(struct NAME##Array));                       \
}                                                                       \
                                                                        \
void free##NAME##Array(NAME##Array array) {                             \
    free(array->data);                                                  \
    free(array);                                                        \
}                                                                       \
                                                                        \
TYPE pop##NAME##Array(NAME##Array array) {                              \
    TYPE temp = array->data[array->used - 1];                           \
    array->data[array->used - 1] = 0;                                   \
    array->used -= 1;                                                   \
                                                                        \
    if (array->size > 8 && array->used < array->size / 2) {             \
        array->data = realloc(array->data, array->size / 2);            \
        array->size /= 2;                                               \
    }                                                                   \
                                                                        \
    return temp;                                                        \
}

#endif
