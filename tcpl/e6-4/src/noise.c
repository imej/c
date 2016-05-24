/* exercise 6-3: noise words. */
#include "header.h"

/* createKeyTree: create a tree of noise words. */
struct tnode *createKeyTree()
{
    char *ka[] = {
	"a",
	"an",
	"and",
	"or",
        "the",
    };
    return fromSortedArray(ka, 0, 4);
}
