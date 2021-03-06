/* exercise 4-6: Add commands for handling variables. Add a variable for 
                 the most recently printed value.
   - v - is the command for variables.
     vp is the most recently printed value.
 */

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <string.h>
#include <math.h>

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
void dup(void);
void swap(void);
void clear(void);
void execFunc(char s[]);

int sp = 0;          /* next free stack position */
double val[MAXVAL];  /* value stack */
char buf[BUFSIZE];   /* buffer for ungetch */
int bufp = 0;        /* next free position in buf */
double lastPrinted;  /* variable */

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
	case '=':
	    printf("\t%.8g\n", pop());
	    break;
	case 'p':
	    printTop();
	    break;
	case 'd':
	    dup();
	    break;
	case 's':
	    swap();
	    break;
	case 'c':
	    clear();
	    break;
	case 'l':
	    execFunc(s);
	    break;
	case 'v':
            if (strcmp(s, "p") == 0) {
	        push(lastPrinted);
	    } else {
	        printf("error: unknown variable %s\n", s);
	    }
	    break;
	case '\n':
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

    if (c == 'l') { /* library function */
        while ((s[i++] = d = getch()) != ' ' && d != '\t' && d != '\n')
	    ;
	s[--i] = '\0';
	return c;
    }

    if (c == 'v') {  /* variable */
        while ((s[i++] = d = getch()) != ' ' && d != '\t' && d != '\n')
	    ;
	s[--i] = '\0';
	return c;
    }

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

/* execFunc: execute function */
void execFunc(char s[])
{
    double tmp;
    if (strcmp(s, "sin") == 0) {
        push(sin(pop()));
    } else if (strcmp(s, "exp") == 0) {
        push(exp(pop()));
    } else if (strcmp(s, "pow") == 0) {
        tmp = pop();
	push(pow(pop(), tmp));
    } else {
        printf("We don't support function %s now.\n", s);
    }
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
        lastPrinted = val[sp-1];  /* remember the last printed value
	                             for the variable function */
        printf("\tTop value of the stack is: %.8g\n", val[sp-1]);    
    } else {
        printf("error: stack empty\n");
    }
}

/* dup: duplicate the top value */
void dup(void)
{
    if (sp > 0) {
        val[sp] = val[sp-1];
	sp++;
    } else {
        printf("error: stack empty\n");
    }
}

/* swap: swap the top two values */
void swap(void)
{
    double tmp;
    if (sp > 1) {
        tmp = val[sp-1];
	val[sp-1] = val[sp-2];
	val[sp-2] = tmp;
    }
}

/* clear: clear stack */
void clear(void)
{
    sp = 0;
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
