/* Exercise 6-3 
 * This is the defination of the tree funcitons 
 */
#include "header.h"

/* talloc: new tree node */
struct tnode * talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* addtree: add a node to the tree */
struct tnode * addtree(struct tnode *p, char *w, int ln)
{
    int cond;

    if (p == NULL) {
        p = talloc();
	if (p == NULL) {
	    return NULL;
	}

	p->word = strdup(w);
	p->lnums = addlnode(NULL, ln);
	p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        /* existing: add line number */
	p->lnums = addlnode(p->lnums, ln);
    } else if (cond < 0) {
        p->left = addtree(p->left, w, ln);
    } else {
        p->right = addtree(p->right, w, ln);
    }

    return p;
}

/* treeprint: in-order print of tree */
void treeprint(struct tnode *p)
{
    struct lnode *l;

    if (p != NULL) {
        treeprint(p->left);

	printf("%s: ", p->word);
        l = p->lnums;
	while (l != NULL) {
	    printf("%d", l->ln);
	    l = l->nxt;
	    if (l != NULL) {
	        printf(", ");
	    }
	}
	printf("\n");

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

	if (rt->lnums != NULL) {
	    destroy_all_lnode(rt->lnums);
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
    root->word = strdup(*(words + mid));
    root->lnums = NULL;
    root->left = fromSortedArray(words, start, mid - 1);
    root->right = fromSortedArray(words, mid +1, end);

    return root;
}
