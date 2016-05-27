/* header file of read */
#ifndef __read_h__
#define __read_h__

#define BUFSIZE 100

int getch(void);   /* get a (possibly pushed back) character */
void ungetch(int c);  /* push character back on input */

#endif
