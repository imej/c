/* copy input to output, replacing:
   tab by \t
   backspace by \b
   backslash by \\ */
/* it turns out that catching backspace key needs special code. Google */   
#include <stdio.h>

int main(void)
{
    char op[300];
    int c;
    int i = 0;
    int j = 0;

    while (i < 300 && ((c = getchar()) != EOF)) {
        op[i] = c;
	i++;
    }

    while (j < i) {
        switch (op[j]) {
	    case '\t':
	        putchar('\\');
		putchar('t');
		break;
            case '\b':
	        putchar('\\');
		putchar('b');
		break;
	    case '\\':
	        putchar('\\');
	        putchar('\\');
		break;
	    default:
	        putchar(op[j]);
	}
	j++;
    }
    putchar('\n');
    printf("had %d backspaces\n", nb);
    return 0;
}
