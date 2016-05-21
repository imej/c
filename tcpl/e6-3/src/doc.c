/* Exercise 6-3: This file contains functions to handle document. */
#include "header.h"

/* doc2tree: read a document and create a tree with all its words. 
 *           a word: 1) only contains letters, digit, -, '
 *                   2) cannot start or end with - or ' 
 */
struct tnode * doc2tree(struct tnode * keytree)
{
    char line[MAXLINE] = {0};
    char word[MAXLINE] = {0};
    int start;
    int lnum = 0;

    struct tnode *tree = NULL;
    struct tnode *noise = createKeyTree();

    while (catchline(line, MAXLINE) > 0) {
         lnum++;
	 start = 0;
	 while ((start = getword(line, start, noise, word)) >= 0) {
	     tree = addtree(tree, word, lnum);
	 }
    }

    return tree;

}
