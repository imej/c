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
