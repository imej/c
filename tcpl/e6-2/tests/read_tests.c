/* this test does not use the minunit.h. */
#include <header.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000   /* NAIVE: a line cannot hold characters more than 1000. */

int main(void)
{
    char s[MAXLINE] = {0};
 
    printf("Start testing catchline() \n");
    printf("Please enter something:");
    catchline(s, MAXLINE);
    printf("You entered: %s", s);

    return 0;
}
