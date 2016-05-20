/* Exercise 6-3: 
 * This file contains functions to handle lnode 
 */
#include "header.h"

struct lnode * addlnode(struct lnode *p, int ln) 
{
    struct lnode *q = (struct lnode *) malloc(sizeof(struct lnode));

    if (q == NULL) {
        return NULL;
    }

    q->ln = ln;
    q->nxt = p;

    return q;
}

void destroy_all_lnode(struct lnode *p)
{
    struct lnode *q = p;

    while (q != NULL) {
        q = p->nxt;
	free(p);
	p = q;
    }
}
