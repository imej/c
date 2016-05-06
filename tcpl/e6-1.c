#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define BUFSIZE 100

char buf[BUFSIZE];   /* buffer for ungetch */
int bufp = 0;        /* next free position in buf */

struct key {
    char *word;
    int count;
} keytab[] = {
    {"auto", 0},
    {"break", 0},
    {"case", 0},
    {"char", 0},
    {"const", 0},
    {"continue", 0},
    {"default", 0},
    {"else", 0},
    {"for", 0},
    {"if", 0},
    {"int", 0},
    {"unsigned", 0},
    {"void", 0},
    {"volatile", 0},
    {"while", 0}
};

#define NKEYS (sizeof keytab / sizeof(struct key))

int getword(char *, int);
int binsearch(char *, struct key *, int);
void ignorePreprocessor();

int isEscape;  

/* count C keywords */
int main(void)
{
    int n;
    char word[MAXWORD];

    ignorePreprocessor();
    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
	    if ((n = binsearch(word, keytab, NKEYS)) >= 0) {
	        keytab[n].count++;
	    }
	}

	if (word[0] == '\n') {
	    ignorePreprocessor();
	}
    }

    for (n = 0; n < NKEYS; n++) {
        if (keytab[n].count > 0) {
	    printf("%4d %s\n", keytab[n].count, keytab[n].word);
	}
    }
    return 0;
}

/* binsearch: find word in tab[0]... tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{
    int cond;
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high) {
        mid = (low+high) / 2;
	if ((cond = strcmp(word, tab[mid].word)) < 0) {
	    high = mid - 1;
	} else if (cond > 0) {
	    low = mid + 1;
	} else {
	    return mid;
	}
    }

    return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
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

int getch(void)   /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)  /* push character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else 
        buf[bufp++] = c;
}

/* ignorePreprocessor: ignore the preprocessor lines.
   I think preprocessor lines start with # and go all the way to the end of the line. 
   If the line is ended with \, the next line is continued too. */
void ignorePreprocessor()
{
    int c, d;
    if ((c = getch()) != '#') {
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
