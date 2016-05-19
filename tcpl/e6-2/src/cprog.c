/* Exercise 6-2: This file contains functions that are related to deal with c program files. */
#include "header.h"

/* isPrepro: check if a line is a preprocesser macro.
 *             I believe a line is a macro if its first non-space character is #, 
 *             or it is after a line that is a macro and ends with a \
 *
 * paras: 1) char line[] - the line of c code that needs to be checked.
 *                         it ends with '\0'.
 *        2) int *inpp - a pointer to an int to indicate if the current line is
 *                       within a uncompleted preprocesser macro, which means 
 *                       it is after a line that is a macro and ends with a \.
 *                       The int might be modified by this function.
 *
 * return: 1 - the curent line is a macro
 *         0 - the current line is NOT a macro
 */
int isPrepro(char line[], int *inpp)
{
    int i;

    if (*inpp) {
         for (i = 0; line[i] != '\0'; i++)
             ;
         for (i--; isspace(line[i]); i--) 
	     ;
	 if (line[i] != '\\') 
	     *inpp = 0;

	 return 1;
    }

    for (i = 0; isspace(line[i]); i++)
        ;

    if (line[i] == '#') {
         for (i = 0; line[i] != '\0'; i++)
             ;
         for (i--; isspace(line[i]); i--) 
	     ;
	 if (line[i] == '\\') 
	     *inpp = 1;
	 else 
	     *inpp = 0;
        
	 return 1;
    }

    return 0;
}

void rmvPrepro(char line[], int *inpp)
{
    if (isPrepro(line, inpp)) {
        line[0] = '\0';
    }
}

/* rmvCmmts: remove comments from a line of a c program. 
 *           It only recognises c comments - slash star star slash.
 * 
 * paras: 1) char line[] - the line of c code that needs to be checked.
 *                         it ends with '\0'.
 *        2) int *inCmmts - a pointer to an int to indicate if the current line is
 *                          within a uncompleted comments.
 *                          The int might be modified by this function.
 *
 * return: void 
 */
void rmvCmmts(char line[], int *inCmmts)
{
    int i = 0;
    int k = 0;
    int j = 0;
    char *str;

    for (i = 0; line[i++] != '\0'; )
        ;

    str = malloc((size_t)i);

    if (str == NULL) 
        return;

    if (*inCmmts) {
        for (k = 0; k < i-2; k++) {
	    if (line[k] == '*' && line[k+1] == '/') {
	        *inCmmts = 0;
                break;
	    }
	}

	if (*inCmmts) {  /* the whole line is comments */
	    line[0] = '\0';
	    return;
	} else {
	    k += 2;
	}
    }

    /* in case, there are more comments in the line. */
    while (line[k] != '\0') {
        if (line[k] == '/' && line[k+1] == '*') {
	    *inCmmts = 1;
            for (k += 2; k < i-2; k++) {
	        if (line[k] == '*' && line[k+1] == '/') {
		    *inCmmts = 0;
		    k++;
		    break;
		}
	    }
	} else {
	    str[j++] = line[k];
	}

	k++;
    }

    str[j] = '\0';

    for (i = 0; (line[i] = str[i]) != '\0'; i++)
        ;   
}

/* getVar: search a string from the start posion to get next C variable. 
 *         a C variable must:
 *         1) only contains letters and/or digits and/or _
 *         2) must start with a letter or _
 *         3) must not be a C keyword
 * params: char line[] - the string to search
 *         int start - the position to begin the searching, must >= 0
 *         struct tnode *keytree - a b-tree holds all keywords
 *         char rv[] - the variable found.
 *
 * return: int >= 0 the position next to the last character of the variable is found.        
 *             -1 find nothing
 */
int getvar(const char line[], const int start, struct tnode *keytree, char rv[])
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
    for (; i < len && !isalpha(line[i]) && line[i] != '_'; i++) {
        ;
    }

    if (i == len) {
        return -1;
    }

    j = 0;
    rv[j] = line[i];
    for (j++, i++; isalnum(line[i]) || line[i] == '_'; i++, j++) {
        rv[j] = line[i];
    }

    rv[j] = '\0';
    rp = i;

    if (intree(keytree, rv)) {
        goto nxt;
    } else {
        return rp;
    }
}
