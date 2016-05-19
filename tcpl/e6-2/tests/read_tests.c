/* this test does not use the minunit.h. */
#include <header.h>
#include <stdio.h>
#include <string.h>

#define MAXLINE 1000   /* NAIVE: a line cannot hold characters more than 1000. */

int main(void)
{
    char s[MAXLINE] = {0};
    int inpp = 0;
    int inCmmts = 0;
/* 
    while (catchline(s, MAXLINE) > 0) {
        printf("------------------------\n");
        printf("%s\n", s);
        rmvPrepro(s, &inpp);
        rmvCmmts(s, &inCmmts);

        printf("%s\n", s);
       
    }
*/
    return 0;
}
