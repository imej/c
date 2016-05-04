/* modify undcl so that it does not add redundant parentheses to declarations */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100
#define MAXOUT 1000

char buf[BUFSIZE];   /* buffer for ungetch */
int bufp = 0;        /* next free position in buf */

enum {NAME, PARENS, BRACKETS};

int gettoken(void);

int tokentype;             /* type of last token */
char token[MAXTOKEN];      /* last token string */
char name[MAXTOKEN];       /* identifier name */
char datatype[MAXTOKEN];   /* data type = char, int, etc. */
char out[MAXOUT];            /* output string */

int main(void)
{
    int type;
    char temp[MAXTOKEN];
    int hasptr;             /* indicate last token was a pointer. 
                               when == 1, we need to parentheses the current out 
			       if the current token is PARENS or BACKETS.
                               */

    while (gettoken() != EOF) { 
	strcpy(out, token);
	hasptr = 0;
	while ((type = gettoken()) != '\n') {
	    if (type == PARENS || type == BRACKETS) {
	        if (hasptr) {
		    sprintf(temp, "(%s)", out);
		    strcpy(out, temp);
		    strcat(out, token);
		    hasptr = 0;
		} else {
	            strcat(out, token);
		}
	    } else if (type == '*') {
	        sprintf(temp, "*%s", out);
		strcpy(out, temp);
		hasptr = 1;
	    } else if (type == NAME) {
	        sprintf(temp, "%s %s", token, out);
		strcpy(out, temp);
	    } else 
	        printf("invalid input at %s\n", token);
	}
	printf("%s\n", out);
    }

    return 0;
}

/* return next token */
int gettoken(void)     
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;
    
    if (c == '(') {
        if ((c = getch()) == ')') {
	    strcpy(token, "()");
	    return tokentype = PARENS;
	} else {
	    ungetch(c);
	    return tokentype = '(';
	}
    } else if (c == '[') {
        for (*p++ = c; (*p++ = getch()) != ']'; )
	    ;
	*p = '\0';
	return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        for (*p++ = c; isalnum(c = getch()); )
	    *p++ = c;
	*p = '\0';
	ungetch(c);
	return tokentype = NAME;
    } else {
        return tokentype = c;
    }
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
