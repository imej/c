/* exercise 4-7: ungets(char []): push back an entire string onto the input. */
#include <stdio.h>

#define BUFSIZE 100

char buf[BUFSIZE];   /* buffer for ungetch */
int bufp = 0;        /* next free position in buf */

int getch(void);   /* get a (possibly pushed back) character */
void ungetch(int c);  /* push character back on input */
void ungets(char s[]);  /* push back an entire string onto the input */

int main(void)
{
    char str[BUFSIZE];
    int i = 0;
    while ((str[i++] = getch()) != '\n') {
        ;
    }

    str[--i] = '\0';

    printf("I got: %s\n", str);

    ungets(&str[i /= 2]);

    i = 0;
    while ((str[i++] = getch()) != '\n') {
        ;
    }
    
    str[--i] = '\0';

    printf("I returned and got again: %s\n", str);
    
    return 0;
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

void ungets(char s[])  /* push back an entire string onto the input */
{
    int i = 0;
    if (s != NULL) {
        for (i = 0; s[i] != '\0'; i++) {
	    ungetch(s[i]);
	}
    }
}
