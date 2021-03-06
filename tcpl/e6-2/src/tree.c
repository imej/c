/* Exercise 6-2 
 * This is the defination of the tree funcitons 
 */
#include "header.h"

/* talloc: new tree node */
struct tnode * talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* strdup: duplicate string */
char * mystrdup(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }

    return p;
}

/* addtree: add a node to the tree */
struct tnode * addtree(struct tnode *p, char *w)
{
    int cond;

    if (p == NULL) {
        p = talloc();
	p->word = mystrdup(w);
	p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        /* existing: do nothing */
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }

    return p;
}

/* treeprint: in-order print of tree */
void treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
	printf("%s\n", p->word);
	treeprint(p->right);
    }
}

/* tdestroy: free tree - nodes and strings */
void tdestroy(struct tnode *rt)
{
    if (rt != NULL) {
        tdestroy(rt->left);
	tdestroy(rt->right);

	if (rt->word != NULL) {
	    free(rt->word);
	}

	free(rt);
    }
}

/* fromSortedArray: create a b-tree from the passed in sorted array.
 */
struct tnode * fromSortedArray(char **words, int start, int end)
{
    int mid;
    struct tnode *root;

    if (words == NULL || start > end) {
        return NULL;
    }

    mid = start + (end - start) / 2;
    root = talloc();
    root->word = mystrdup(*(words + mid));
    root->left = fromSortedArray(words, start, mid - 1);
    root->right = fromSortedArray(words, mid +1, end);

    return root;
}

/*searchtree: search for a word in the tree */
struct tnode * searchtree(struct tnode *tree, const char *wd)
{
    struct tnode *p = tree;

    if (p == NULL || wd == NULL) {
        return NULL;
    }

    if (strcmp(p->word, wd) < 0) {
        p = searchtree(p->right, wd);
    } else if (strcmp(p->word, wd) > 0){
        p = searchtree(tree->left, wd);
    } 

    return p;
}

/*intree: if a string is in a tree */
int intree(struct tnode *tree, const char *wd)
{
    struct tnode *p = searchtree(tree, wd);
    if (p == NULL) {
        return 0;
    } else {
        return 1;
    }
}

/* prtgrp: print in alphabetical order each group of variable names that are
 *         identical in the first num characters. 
 */
void prtgrp(struct tnode *p, int num, char *grp)
{
    int len, i;
    char tmp[MAXLINE] = {0};

    if (p != NULL && num > 0) {
        prtgrp(p->left, num, grp);

	/* print self */
	if (p->word != NULL) {
	    for (len = 0; *(p->word + len) != '\0'; len++) {
	        ;
	    }

	    if (num <= len) {
	        /* only print when there are enough characters. */
                for (i = 0; i < num; i++) {
		    tmp[i] = *(p->word + i);
		}

		tmp[i] = '\0';

		if (strcmp(grp, tmp) != 0) {
		    /* new group */
                    strcpy(grp, tmp);
		    printf("---- Group: %s:\n", grp);
		}

		printf("%s\n", p->word);
	    }
	}

	prtgrp(p->right, num, grp);
    }
}

