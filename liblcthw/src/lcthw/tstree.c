#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <lcthw/dbg.h>
#include <lcthw/tstree.h>

static inline TSTree *TSTree_insert_base(TSTree *root, TSTree *node, const char *key, size_t len, void *value)
{
    if (node == NULL) {
        node = (TSTree *) calloc(1, sizeof(TSTree));

	if (root == NULL) {
	    root = node;
	}

	node->splitchar = *key;
    }

    if (*key < node->splitchar) {
        node->low = TSTree_insert_base(root, node->low, key, len, value);
    } else if (*key == node->splitchar) {
        if (len > 1) {
	    node->equal = TSTree_insert_base(root, node->equal, key + 1, len - 1, value);
	} else {
	    assert(node->value == NULL && "Duplicate insert into tst.");
	    node->value = value;
	}


    }
}
