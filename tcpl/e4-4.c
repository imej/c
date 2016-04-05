/* exercise 4-4: 
   - new command p to print the top element of the stack without poping.
   - new command u to duplicate the top element
   - new command s to swap the top two elements
   - new command c to clear the stack
 */

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
void printTop(void);
int getch(void);
void ungetch(int);

int sp = 0;          /* next free stack position */
double val[MAXVAL];  /* value stack */
char buf[BUFSIZE];   /* buffer for ungetch */
int bufp = 0;        /* next free position in buf */

/* reverse Polish calculator */
int main(void)
{
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s)) != EOF) {
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
	case '%':
	    op2 = pop();
	    if (op2 != 0.0) {
	        push((double)((int)pop() % (int)op2));
	    } else {
	        printf("error: zero divisor\n");
	    }
	    break;
	case '\n':
	    printf("\t%.8g\n", pop());
	    break;
	case 'p':
	    printTop();
	    break;
	default:
	    printf("error: unknown command %s\n", s);
	    break;
	}
    }
    return 0;
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c, d;

    i = 0;
    while ((s[0] = c = getch()) == ' ' || c == '\t')
        ;
    s[1] = '\0';
    if(!isdigit(c) && c != '.' && c != '+' && c != '-') {
        return c;     /* not a number */
    } else if (c == '+' || c == '-') {
        d = getch();
        if (!isdigit(d)) {
	    ungetch(d);
	    return c;  /* not a number */
	} else {
	    s[1] = d;
	    s[2] = '\0';
	    i = 1;
	}
    }

    if (isdigit(c) || i == 1 ) {   /* collect integer part */
        while (isdigit(s[++i] = c = getch()))
	    ;
    }

    if (c == '.') {     /* collect fraction part*/
        while (isdigit(s[++i] = c = getch()))
	    ;
    }

    s[i] = '\0';
    if (c != EOF) {
        ungetch(c);
    }

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

/* printTop: print the top value without poping */
void printTop(void)
{
    if (sp > 0) {
        printf("\tTop value of the stack is: %.8g\n", val[sp-1]);    
    } else {
        printf("error: stack empty\n");
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
