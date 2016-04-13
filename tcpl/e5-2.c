/* exercise 5-2 getfloat */
#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

char buf[BUFSIZE];   /* buffer for ungetch */
int bufp = 0;        /* next free position in buf */

int getfloat(float *);
int getch(void);   
void ungetch(int c); 

int main(void) 
{
    float a = 0.0;
    int b;

    getfloat(&a);
    printf("a = %f\n", a);

    b = getch();
    if (b != EOF) {
        printf("b = %c\n", b);
    }
    return 0;
}

/* getfloat: get next float from input into *pn */
int getfloat(float *pn)
{
    int c, d, sign, pw;

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

    pw = 1;
    if (c == '.') {
        d = getch();
        if (isdigit(d)) {
	    c = d;
	    *pn = 10 * *pn + (c - '0');
            pw = 10;
	    while (isdigit(c = getch())) {
	        *pn = 10 * *pn + (c - '0');
		pw *= 10;
	    }
	} else {
	    ungetch(d);
	    ungetch(c);
	}
    }

    *pn /= pw;
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
