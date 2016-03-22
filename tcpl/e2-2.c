/* a loop equivalent to:
   for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
       s[i] = c;
 */
#include <stdio.h>
#define LIMIT 10

int main(void)
{
    int lim = LIMIT;
    int c;
    int i = 0;
    char s[LIMIT];

    for (i=0; i<lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
        s[i] = c;
    /*   
    while (i < lim -1) {
        c = getchar();

        if (c == '\n') {
	    break;
	}

	if (c == EOF) {
	    break;
	}

        s[i] = c;
        ++i;
    }
    */
    s[i] = '\0';

    printf("You have entered: %s", s);
    return 0;
}
