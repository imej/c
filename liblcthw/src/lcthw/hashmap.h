#ifndef _lcthw_Hashmap_h
#define _lcthw_Hashmap_h

#include <stdint.h>
#include <lcthw/darray.h>

#define DEFAULT_NUMBER_OF_BUCKETS 3

typedef int (*Hashmap_compare)(void *a, void *b);
typedef uint32_t (*Hashmap_hash)(void *key);
typedef int (*Hashmap_free_key)(void *key);

typedef struct Hashmap {
    DArray * buckets;
    Hashmap_compare compare;
    Hashmap_hash hash;
    Hashmap_free_key free_key;
} Hashmap;

typedef struct HashmapNode {
    void * key;
    void * data;
    uint32_t hash;
} HashmapNode;

typedef int (*Hashmap_traverse_cb)(HashmapNode * node);

Hashmap * Hashmap_create(Hashmap_compare compare, Hashmap_hash hash, Hashmap_free_key free_key);
void Hashmap_destroy(Hashmap *map);

int Hashmap_set(Hashmap * map, void * key, void * data);
void * Hashmap_get(Hashmap * map, void * key);

int Hashmap_traverse(Hashmap * map, Hashmap_traverse_cb traverse_cb);

void * Hashmap_delete(Hashmap * map, void * key);

#endif
