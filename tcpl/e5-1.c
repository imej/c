/* exercise 5-1 fix getint to handle +|-0 */
#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

char buf[BUFSIZE];   /* buffer for ungetch */
int bufp = 0;        /* next free position in buf */

int getint(int *);
int getch(void);   
void ungetch(int c); 

int main(void) 
{
    int a = 0;
    int b;

    getint(&a);
    printf("a = %d\n", a);

    b = getch();
    if (b != EOF) {
        printf("b = %c\n", b);
    }
    return 0;
}

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
    int c, d, sign;

    while (isspace(c = getch()))  /* skip white space */
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);     /* it's not a number */
	return 0;
    }

    if (c == '+' || c == '-') {
        d = getch();
	if (isdigit(d) && d != '0') {
	    ungetch(d);
	} else {
	    ungetch(d);
	    ungetch(c);
	    return 0;
	}
    }

    sign = (c == '-') ? -1 : 1;
    if (c == '+' || c == '-')
        c = getch();
    for (*pn = 0; isdigit(c); c = getch()) {
        *pn = 10 * *pn + (c - '0');
    }

    *pn *= sign;
    if (c != EOF)
        ungetch(c);
    return c;
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
