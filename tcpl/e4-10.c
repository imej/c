/* exercise 4-10: use catchline to read the entire input line. */
#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>

#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define MAXVAL 100   /* maximum depth of val stack */
#define BUFSIZE 100

int getop(char[]);
void push(double);
double pop(void);
int catchline(char s[], int lim);

int sp = 0;          /* next free stack position */
double val[MAXVAL];  /* value stack */
char line[BUFSIZE];
int lnlen;
int lnp;

/* reverse Polish calculator */
int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while ((lnlen = catchline(line, BUFSIZE)) > 0) {
        lnp = 0;
        while ((type = getop(s)) != EOF && type != '\0') {
            switch (type) {
	    case NUMBER:
	        push(atof(s));
	        break;
	    case '+':
	        push(pop() + pop());
	        break;
	    case '*':
	        push(pop() * pop());
	        break;
	    case '-':
	        op2 = pop();
	        push(pop() - op2);
	        break;
	    case '/':
	        op2 = pop();
	        if (op2 != 0.0) {
	            push(pop() / op2);
	        } else {
	            printf("error: zero divisor\n");
	        }
	        break;
	    case '\n':
	        printf("\t%.8g\n", pop());
	        break;
	    default:
	        printf("error: unknown command %s\n", s);
	        break;
            }
        }
	
	if (type == EOF) {
	    break;
	}
    }
    return 0;
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;

    while ((s[0] = c = line[lnp]) == ' ' || c == '\t')
        lnp++;
    s[1] = '\0';
    if(!isdigit(c) && c != '.') {
        lnp++;
        return c;     /* not a number */
    }

    i = 0;
    if (isdigit(c)) {   /* collect integer part */
        while (isdigit(s[++i] = c = line[++lnp]))
	    ;
    }

    if (c == '.') {     /* collect fraction part*/
        while (isdigit(s[++i] = c = line[++lnp]))
	    ;
    }

    s[i] = '\0';
    /* if (c != EOF) {
        lnp--;
    } */

    return NUMBER;
}

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %g\n", f);
    }
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
	return 0.0;
    }
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
