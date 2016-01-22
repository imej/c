#include <stdio.h>

int test(void)
{
    int outer = 8;

    {
        int insider = 10;
	printf("insider = %d\n", insider);
	printf("++outer = %d\n", ++outer);
	
    }

    printf("outer = %d\n", outer);

    /* compiling error: insider is not declared. */
    /* printf("insider = %d\n", insider); */

   
}

int main(void)
{
    test();

    return 0;
}
