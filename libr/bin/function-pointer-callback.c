#include <stdio.h>

int count(int from, int to, void (*myOut)(int i))
{
    int j = 0,
        rv = 0;

    if (from >= to) {
        rv = -1;
    } else {
        for(j = 0; j < to - from; j++) {
	    rv += from + j;
	}
    }

    (*myOut)(rv);

    return 0;
}

void displayU(int i)
{
    /* display the result in upper case. */
    printf("WE GOT: %d\n", i);
}

void displayL(int i)
{
    /* display the result in lower case. */
    printf("we got: %d\n", i);
}

int main()
{
    count(1, 50000, &displayU);
    count(10, 5, &displayL);

    printf("all done.\n");

    return 0;
}
