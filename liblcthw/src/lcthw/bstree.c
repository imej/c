#include <lcthw/bstree.h>

static int Default_compare(void *a, void *b)
{
    // By default, the key is a int
    return *(int *)a - *(int *)b;
}

static int Default_key_destroy(void *key)
{
    // Do nothing
    return (key == NULL ? 0 : 0);
}

static int Default_data_destroy(void *data)
{
    // Do nothing
    return (data == NULL ? 0 : 0);
}

BSTree *BSTree_create(BSTree_compare compare, BSTree_key_destroy key_destroy, BSTree_data_destroy data_destroy)
{
    BSTree *map = calloc(1, sizeof(BSTree));

    map->compare = compare;
    map->key_destroy = key_destroy == NULL ? Default_key_destroy : key_destroy;
    map->data_destroy = data_destroy == NULL ? Default_data_destroy : data_destroy;
    map->count = 0;
    map->root = NULL;

    return map;
}

void BSTree_delete_subtree(BSTree *map, BSTreeNode *node)
{
    if (node != NULL) {
        if (node->left == NULL && node->right == NULL) {
	    // Leaf node, delete
	    if (node->parent != NULL) {
	        if (node->parent->left == node) {
	            node->parent->left = NULL;
	        } else {
		    node->parent->right = NULL;
		}
	    }

            map->key_destroy(node->key);
	    map->data_destroy(node->data);
	    free(node);
	} else {
	    if (node->left != NULL) {
	        BSTree_delete_subtree(map, node->left);
	    }

	    if (node->right != NULL) {
	        BSTree_delete_subtree(map, node->right);
	    }
	}
    }
}

void BSTree_destroy(BSTree *map)
{
    BSTree_delete_subtree(map, map->root); 
    free(map);
}

BSTreeNode *BSTree_search(BSTree *map, void *key, BSTreeNode *node)
{
    if (node == NULL || map->compare(key, node->key) == 0) {
        return node;
    } else if (map->compare(key, node->key) < 0) {
        BSTree_search(map, key, node->left);
    } else {
 	BSTree_search(map, key, node->right);
    }
}

void *BSTree_get(BSTree *map, void *key)
{
    assert(map != NULL && key != NULL);
    BSTreeNode *temp =  BSTree_search(map, key, map->root);
    if (temp != NULL) {
        return temp->data;
    } else {
        return NULL;
    }
}

BSTreeNode *BSTree_new_node(void *key, void *data, BSTreeNode *parent)
{
    BSTreeNode *temp = calloc(1, sizeof(BSTreeNode));
    assert(temp != NULL);
    temp->key = key;
    temp->data = data;
    temp->parent = parent;

    return temp;
}

BSTreeNode *BSTree_insert(BSTree *map, BSTreeNode *node, void *key, void *data)
{
    if (node == NULL) {
        // Empty tree, add as root
        node = BSTree_new_node(key, data, NULL);
	map->root = node;
	map->count += 1;
	return node;
    } else if (map->compare(key, node->key) == 0) {
        // Update data
        node->data = data;
	return node;
    } else if (map->compare(key, node->key) < 0) {
        // Insert to left
	if (node->left == NULL) {
	    node->left = BSTree_new_node(key, data, node);
	    map->count += 1;
	    return node->left;
	} else {
	    BSTree_insert(map, node->left, key, data);
	}
    }else if (map->compare(key, node->key) > 0) {
        // Insert to right
	if (node->right == NULL) {
	    node->right = BSTree_new_node(key, data, node);
	    map->count += 1;
	    return node->right;
	} else {
	    BSTree_insert(map, node->right, key, data);
	}
    }
}

int BSTree_set(BSTree *map, void *key, void *data)
{
    if (BSTree_insert(map, map->root, key, data) != NULL) {
        return 0;
    } else {
        return 1;
    }
}
