/* count blanks, tabs and newlines */
#include <stdio.h>

main()
{
    int c;
    int cb = 0;
    int ct = 0;
    int cn = 0;
    
    while ((c = getchar()) != EOF) {
        if (c == ' ') {
	    cb++;
	} else if (c == '\t') {
	    ct++;
	} else if (c == '\n') {
	    cn++;
	}
    }

    printf("\nblanks = %d", cb);
    printf("\ntabs = %d", ct);
    printf("\nnewlines = %d\n", cn);
}
