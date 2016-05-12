/* Exercise 6-2
 * This is the declaration part of the tree functions
 */
#ifndef __dbg_h__
#define __dbg_h__

#include <stdio.h>
#include <stdlib.h>

#endif

/* tnode: tree node */
struct tnode {
    char *word;
    struct tnode *left;
    struct tnode *right;
};

struct tnode * talloc(void);
char * mystrdup(char *s);
struct tnode * addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
void tdestroy(struct tnode *rt);
