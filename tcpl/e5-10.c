/* exercise 5-10: expr 2 3 4 + * 
   - I will only support + - * /
   - I assume the numbers are integers
 */

#include <stdio.h>
#include <stdlib.h> 
#include <ctype.h>

#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */
#define MAXVAL 100   /* maximum depth of val stack */
#define BUFSIZE 100

void push(int);
int pop(void);

int sp = 0;          /* next free stack position */
int val[MAXVAL];     /* value stack */
char buf[BUFSIZE];   /* buffer for ungetch */
int bufp = 0;        /* next free position in buf */

/* reverse Polish calculator */
int main(int argc, char *argv[])
{
    int type;
    double op2;

    printf("argc = %d\n", argc);

    while (--argc > 0) {
        if (isdigit(type = (*++argv)[0])) {
	    push(atoi(*argv));
	} else {
	    switch (type) {
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
	        
	    }
	}
    }

    printf("%d\n", pop());

    return 0;
}

/* push: push f onto value stack */
void push(int f)
{
    if (sp < MAXVAL) {
        val[sp++] = f;
    } else {
        printf("error: stack full, can't push %d\n", f);
    }
}

/* pop: pop and return top value from stack */
int pop(void)
{
    if (sp > 0) {
        return val[--sp];
    } else {
        printf("error: stack empty\n");
	return 0;
    }
}
