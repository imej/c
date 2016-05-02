/* 5-18: make dcl recover from input errors. */
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100
#define BUFSIZE 100

char buf[BUFSIZE];   /* buffer for ungetch */
int bufp = 0;        /* next free position in buf */

enum {NAME, PARENS, BRACKETS};

int dcl(void);
int dirdcl(void);
int gettoken(void);

int tokentype;             /* type of last token */
char token[MAXTOKEN];      /* last token string */
char name[MAXTOKEN];       /* identifier name */
char datatype[MAXTOKEN];   /* data type = char, int, etc. */
char out[1000];            /* output string */

int main(void)
{
    while (gettoken() != EOF) {  /* 1st token on line */
        strcpy(datatype, token); /* is the datatype */
	out[0] = '\0';
	if(dcl() > 0) {        /* parse rest of line */
	    if (tokentype != '\n') {
	        printf("syntax error\n");
	    }
	    printf("%s: %s %s\n", name, out, datatype);
	}
    }

    return 0;
}

/* dcl: parse a declarator
   return 1 if everything was good
   return -1 if not
 */
int dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*'; ) /* count *'s */
        ns++;
    if (dirdcl() > 0) {
        while (ns-- > 0)
            strcat(out, " pointer to");
    } else {
        return -1;
    } 

    return 1;
}

/* dirdcl: parse a direct declarator 
   return 1 if everything was good
   return -1 if not
 */
int dirdcl(void)
{
    int type;

    if (tokentype == '(') {   /* ( dcl )*/
        dcl();
	if (tokentype != ')') {
	    printf("error: missing )\n");
	    return -1;
	}
    } else if (tokentype == NAME)   /* variable name */
        strcpy(name, token);
    else {
        printf("error: expected name or (dcl)\n");
        return -1;
    }

    while ((type = gettoken()) == PARENS || type == BRACKETS) {
        if (type == PARENS) {
	    strcat(out, " function returning");
	} else {
	    strcat(out, " array");
	    strcat(out, token);
	    strcat(out, " of");
	}
    }

    return 1;
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
