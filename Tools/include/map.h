#ifndef c_map_h
#define c_map_h

#include <stdlib.h>
#include <stdint.h>

#define MAP(NAME, TYPEIN, TYPEOUT, HASH, ERROR, DEFAULT)                \
                                                                        \
/* struct containing hash input and output, stored in map */            \
typedef struct {                                                        \
    char isfilled;                                                      \
    int64_t hash;                                                       \
    TYPEIN in;                                                          \
    TYPEOUT out;                                                        \
} NAME##MapItem;                                                        \
                                                                        \
/* struct containing a map, similar to the array struct */              \
typedef struct NAME##Map {                                              \
    int64_t size;                                                       \
    int64_t used;                                                       \
    NAME##MapItem *data;                                                \
} *NAME##Map;                                                           \
                                                                        \
/* function declarations */                                             \
void add##NAME##Map(NAME##Map map, TYPEIN in, TYPEOUT out);             \
TYPEOUT read##NAME##Map(NAME##Map map, TYPEIN in);                      \
NAME##Map init##NAME##Map();                                            \
void free##NAME##Map(NAME##Map map);                                    \
void pop##NAME##Map(NAME##Map map, TYPEIN in);                          \
                                                                        \
                                                                        \
void add##NAME##Map(NAME##Map map, TYPEIN in, TYPEOUT out) {            \
    if (map->used >= map->size / 2) {                                   \
        /* if map is too full create new map */                         \
        /* and re-hash all existing items into new map. */              \
        /* then sub in pointers and values as necessary back */         \
        /* into the original map. */                                    \
                                                                        \
        /* if map was empty just make it not empty */                   \
        NAME##Map new = calloc(1, sizeof(struct NAME##Map));            \
        if (map->size) {                                                \
            new->data = calloc(2 * map->size, sizeof(NAME##MapItem));   \
                                                                        \
            new->size = 2 * map->size;                                  \
            for (int i = 0; i < map->size; i++) {                       \
                if (map->data[i].isfilled)                              \
                    add##NAME##Map(new, map->data[i].in,                \
                                   map->data[i].out);                   \
            }                                                           \
                                                                        \
            free(map->data);                                            \
            map->data = new->data;                                      \
            map->size = new->size;                                      \
                                                                        \
            free(new);                                                  \
                                                                        \
        } else {                                                        \
            map->data = calloc(16, sizeof(NAME##MapItem));              \
            map->size = 16;                                             \
        }                                                               \
    }                                                                   \
                                                                        \
    /* if no other problems, hash and find free slot */                 \
    /* if input already in use, then simply overwrite */                \
    /* the while exits either when input found or free slot */          \
    int64_t hash = HASH(in);                                            \
    int64_t index = hash & (map->size - 1);                             \
    while (map->data[index].isfilled && (map->data[index].hash != hash  \
        || map->data[index].in != in))                                  \
        index = (index + 1) & (map->size - 1);                          \
                                                                        \
    map->data[index] = (NAME##MapItem){1, hash, in, out};               \
    map->used += 1;                                                     \
}                                                                       \
                                                                        \
/* read item, and if error flag disabled, return DEFAULT if not found */\
TYPEOUT read##NAME##Map(NAME##Map map, TYPEIN in) {                     \
    int64_t hash = HASH(in);                                            \
    int64_t index = hash & (map->size - 1);                             \
                                                                        \
    while (map->data[index].isfilled && (map->data[index].hash != hash  \
        || map->data[index].in != in))                                  \
        index = (index + 1) & (map->size - 1);                          \
                                                                        \
    if (!(map->data[index].isfilled || ERROR)) {                        \
        return DEFAULT;                                                 \
    }                                                                   \
    else if (!map->data[index].isfilled || map->data[index].in != in) { \
        printf("Error: Item not in map. \n");                           \
        exit(1);                                                        \
    }                                                                   \
                                                                        \
    else return map->data[index].out;                                   \
}                                                                       \
                                                                        \
NAME##Map init##NAME##Map() {                                           \
    return calloc(1, sizeof(struct NAME##Map));                         \
}                                                                       \
                                                                        \
void free##NAME##Map(NAME##Map map) {                                   \
    free(map->data);                                                    \
    free(map);                                                          \
}                                                                       \
                                                                        \
/* pop item, if error and it does not exist, crash. */                  \
void pop##NAME##Map(NAME##Map map, TYPEIN in) {                         \
    int64_t hash = HASH(in);                                            \
    int64_t index = hash & (map->size - 1);                             \
                                                                        \
    while (map->data[index].isfilled && map->data[index].hash != hash)  \
        index = (index + 1) & (map->size - 1);                          \
                                                                        \
    if (!(map->data[index].isfilled || ERROR))                          \
        return;                                                         \
    else if (!map->data[index].isfilled) {                              \
        printf("Error: Item not in map. \n");                           \
        exit(1);                                                        \
    }                                                                   \
                                                                        \
    else map->data[index] = (NAME##MapItem){0};                         \
}

#endif
