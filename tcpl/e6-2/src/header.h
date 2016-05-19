/* Exercise 6-2
 * This is the declaration part of the whole project.
 * It feels like that it is easier to maintain just one giant header file.
 */
#ifndef __header_h__
#define __header_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* tnode: tree node */
struct tnode {
    char *word;
    struct tnode *left;
    struct tnode *right;
};

/* functions in tree.c */
struct tnode *talloc(void);
char *mystrdup(char *s);
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
void tdestroy(struct tnode *rt);
struct tnode * fromSortedArray(char **words, int start, int end);

/* functions in read.c */
int catchline(char s[], int lim);

/* functions in cprog.c */
int isPrepro(char line[], int *inpp);
void rmvCmmts(char line[], int *inCmmts);
void rmvPrepro(char line[], int *inpp);

/* functions in ckeys.c */
struct tnode *createKeyTree();

#endif
