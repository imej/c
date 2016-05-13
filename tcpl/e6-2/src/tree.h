/* Exercise 6-2
 * This is the declaration part of the tree functions
 */
#ifndef __tree_h__
#define __tree_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* tnode: tree node */
struct tnode {
    char *word;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *talloc(void);
char *mystrdup(char *s);
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
void tdestroy(struct tnode *rt);

#endif
