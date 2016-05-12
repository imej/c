/* Updates: 
   2016-05-11: need to check the input one line a time. In this way, it is easier 
               to jump over preprocessors */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 100
#define MAXWORD 100
#define MAXLINE 1000   /* maximum characters a line might contain. */

char buf[BUFSIZE];   /* buffer for ungetch */
int bufp = 0;        /* next free position in buf */

void ignorePreprocessor();
int getch(void);
void ungetch(int c);
int getword(char *word, int lim);

int isEscape;  

/* tnode: tree node */
struct tnode {
    char *word;
    struct tnode *left;
    struct tnode *right;
};

/* talloc: new tree node */
struct tnode *
talloc(void)
{
    return (struct tnode *) malloc(sizeof(struct tnode));
}

/* strdup: duplicate string */
char *
mystrdup(char *s)
{
    char *p;

    p = (char *) malloc(strlen(s) + 1);
    if (p != NULL) {
        strcpy(p, s);
    }

    return p;
}

/* addtree: add a node to the tree */
struct tnode *
addtree(struct tnode *p, char *w)
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
void 
treeprint(struct tnode *p)
{
    if (p != NULL) {
        treeprint(p->left);
	printf("%s\n", p->word);
	treeprint(p->right);
    }
}

/* tdestroy: free tree - nodes and strings */
void 
tdestroy(struct tnode *rt)
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

int 
main(int argc, char *argv[])
{
    char word[MAXWORD];
    struct tnode *tree = NULL;
    struct tnode *root = NULL;

    ignorePreprocessor();
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0]) || word[0] == '_') {
	   tree = addtree(tree, word);
	   if (root == NULL) {
	       root = tree;
	   }
	}

	if (word[0] == '\n') {
	    ignorePreprocessor();
	}
    }

    treeprint(root);
    tdestroy(root);

    return 0;
}

/* getword: get next word or character from input */
int 
getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;

    /* jump over comments */
    if (c == '/') {
        if ((c = getch()) == '*') {
	    while ((c = getch()) != EOF) {
	        if ( c == '*') {
		    if ((c = getch()) == '/') {
		        /* comments over, get next character */
                        while (isspace(c = getch()))
                            ;
		        
		        break;
		    } else {
		        ungetch(c);
		    }
		}
	    }
	} else {
	    ungetch(c);
	    c = '/';
	}
    }

    /* jump over constants */
    if (c == '\"' && !isEscape) {
	while (((c = getch()) != '\"' || isEscape) && c != EOF) {
	    if (c == '\\') {
	        isEscape = 1;
	    } else {
	        isEscape = 0;
	    }
	} 

	if (c != EOF) {
            while (isspace(c = getch()))
                ;
	}
    }

    if (c != EOF) {
        *w++ = c;
	if (c == '\\') {
	    isEscape = 1;
	} else {
	    isEscape = 0;
	}
    }

    if (!isalpha(c) && c != '_') {
        *w = '\0';
	return c;
    }

    for ( ; --lim > 0; w++) {
        *w = getch();
        if (!isalnum(*w) && *w != '_') {
	    ungetch(*w);
	    break;
	}
    }

    *w = '\0';
    return word[0];
}

int 
getch(void)   /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void 
ungetch(int c)  /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else 
        buf[bufp++] = c;
}

/* ignorePreprocessor: ignore the preprocessor lines.
   I think preprocessor lines start with # and go all the way to the end of the line. 
   If the line is ended with \, the next line is continued too. */
void 
ignorePreprocessor()
{
    int c, d;
    if ((c = getch()) != '#') {
        ungetch(c);
        return;
    }
  
    while (isspace(d = getch()))
        ;
    while (d != '\n' || c == '\\') {
        c = d;
        while (isspace(d = getch()))
            ;
    }

    ignorePreprocessor();
}

int catchline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c!= '\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
	++i;
    }

    s[i] = '\0';
    return i;
}
