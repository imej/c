/* exercise 4-8: there will never be more than one character of pushback. */
#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

char buf;   /* buffer for ungetch */
char bufp = 0;

int getch(void);   /* get a (possibly pushed back) character */
void ungetch(int c);  /* push character back on input */
int getInput(char s[]);

int main(void)
{
    char s[BUFSIZE];

    getInput(s);

    printf("%s\n", s);

    return 0;
}

int getInput(char s[])
{
    int i, c;

    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    i = 0;
    while (!isdigit(s[++i] = c = getch())) {
        ;
    }

    s[i] = '\0';

    if (c != EOF)
        ungetch(c);
    return 0;
}

int getch(void)   /* get a (possibly pushed back) character */
{
    if (bufp != 0) {
        bufp = 0;
	return buf;
    } else {
        return getchar();
    }
}

void ungetch(int c)  /* push character back on input */
{
    if (bufp != 0)
        printf("ungetch: existing buffered char\n");
    else {
        bufp = 1; 
        buf = c;
    } 
}
