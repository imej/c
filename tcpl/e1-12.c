/* prints input one word per line */
#include <stdio.h>

int main(void)
{
    char op[301];
    int c, i;

    i = 0;
    while (i < 300 && ((c = getchar()) != EOF)) {
        if (c != ' ' && c != '\n' && c != '\t') {
	    op[i++] = c;
	} else if (i > 0) {
	    c = '\n';
            if (op[i-1] != c) {
	        op[i++] = c;
	    }
	} 
    }

    op[i] = '\0';

    printf("\n%s", op);

    return 0;
}
