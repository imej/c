/* Exercise 6-2: This file contains functions to read the input. */
#include "header.h"

int catchline(char s[], int lim)
{
    int c, i;

    for (i = 0, c = 0; i < lim - 1 && (c = getchar()) != EOF && c!= '\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
	++i;
    }

    s[i] = '\0';
    return i;
}

/* read: */
struct tnode * read() 
{
    char line[MAXLINE] = {0};
    char var[MAXLINE] = {0};
    int inpp = 0;
    int inCmmts = 0;
    int start;

    struct tnode *tree = NULL;
    struct tnode *keys = createKeyTree();

    while (catchline(line, MAXLINE) > 0) {
        rmvPrepro(line, &inpp);
	rmvCmmts(line, &inCmmts);

        start = 0;
	while ((start = getvar(line, start, keys, var)) >= 0) {
	    tree = addtree(tree, var);
	}
    }

    return tree;
}
