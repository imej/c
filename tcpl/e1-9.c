/* copy input to output, replacing each string of 
   one or more blanks by a single blank*/
#include <stdio.h>

main()
{
    char op[301];
    int c, i;

    i = 0;
    while (i < 300 && ((c = getchar()) != EOF)) {
        if (i == 0 || c != ' ' || op[i-1] != ' ') {
	    op[i] = c;
	    i++;
	} 
    }

    op[i] = '\0';

    printf("\n%s", op);
}
