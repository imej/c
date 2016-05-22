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

/* getword: search a string from the start posion to get next word. 
 *           a word: 1) only contains letters, digit, -, '
 *                   2) cannot start or end with - or ' 
 * params: char line[] - the string to search
 *         int start - the position to begin the searching, must >= 0
 *         struct tnode *keytree - a b-tree holds all words to exclude
 *         char rv[] - the word found.
 *
 * return: int >= 0 the position next to the last character of the word is found.        
 *             -1 find nothing
 */
int getword(const char line[], const int start, struct tnode *keytree, char rv[])
{
    int len, i, j, rp;
    
    if (line == NULL || keytree == NULL || start < 0 || rv == NULL) {
        return -1;
    }
    
    for (len = 0; line[len] != '\0'; len++)
        ;
    
    if (start >= len) {
        return -1;
    }

    i = start;

nxt:    
    for (; i < len && !isalnum(line[i]); i++) {
        ;
    }

    if (i == len) {
        return -1;
    }

    j = 0;
    rv[j] = line[i];
    for (j++, i++; isalnum(line[i]) || line[i] == '-' || line[i] == '\''; i++, j++) {
        rv[j] = line[i];
    }

    /* remove last \' or - */

    while (rv[j-1] == '\'' || rv[j-1] == '-') {
        j--;
    }

    rv[j] = '\0';
    rp = i;

    if (intree(keytree, rv)) {
        goto nxt;
    } else {
        return rp;
    }
}
