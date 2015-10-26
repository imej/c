#ifndef _lcthw_BSTree_h
#define _lcthw_BSTree_h

#include <assert.h>
#include <stdlib.h>

typedef int (*BSTree_compare)(void *a, void *b);
typedef int (*BSTree_key_destroy)(void *key);
typedef int (*BSTree_data_destroy)(void *data);

typedef struct BSTreeNode {
    void *key;
    void *data;

    struct BSTreeNode *left;
    struct BSTreeNode *right;
    struct BSTreeNode *parent;
} BSTreeNode;

typedef struct BSTree {
    int count;
    BSTree_compare compare;
    BSTree_key_destroy key_destroy;
    BSTree_data_destroy data_destroy;
    BSTreeNode *root;
} BSTree;

// typedef int (*BSTree_traverse_cb)(BSTreeNode *node);

BSTree *BSTree_create(BSTree_compare compare, BSTree_key_destroy key_destroy, BSTree_data_destroy data_destroy);

void BSTree_destroy(BSTree *map);

int BSTree_set(BSTree *map, void *key, void *data);
void *BSTree_get(BSTree *map, void *key);

// int BSTree_traverse(BSTree *map, BSTree_traverse_cb traverse_cb);

// void *BSTree_delete(BSTree *map, void *key);

#endif
