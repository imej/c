/* Exercise 6-3
 * This is the declaration part of the whole project.
 * It feels like that it is easier to maintain just one giant header file.
 */
#ifndef __header_h__
#define __header_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 3000

/* lnode: node of link to hold line numbers. */
struct lnode {
    int ln;
    struct lnode *nxt;
};

/* tnode: tree node */
struct tnode {
    char *word;
    struct lnode *lnums;
    struct tnode *left;
    struct tnode *right;
};

/* functions in ln.c */
struct lnode * addlnode(struct lnode *p, int ln);
void destroy_all_lnode(struct lnode *p);

/* functions in tree.c */
struct tnode *talloc(void);
struct tnode *addtree(struct tnode *p, char *w, int ln);
void treeprint(struct tnode *p);
void tdestroy(struct tnode *rt);
struct tnode * fromSortedArray(char **words, int start, int end);
struct tnode * searchtree(struct tnode *tree, const char *wd);
int intree(struct tnode *tree, const char *wd);
void prtgrp(struct tnode *p, int num, char *grp);

/* functions in read.c */
int catchline(char s[], int lim);

/* functions in noise.c*/
struct tnode *createKeyTree();

#endif
