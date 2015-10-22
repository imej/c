#include <lcthw/bstree.h>
#include <stdlib.h>

BSTree *BSTree_create(BSTree_compare compare)
{
    BSTree *map = calloc(1, sizeof(BSTree));

    map->compare = compare;
    map->count = 0;
    map->root = NULL;

    return NULL;
}

