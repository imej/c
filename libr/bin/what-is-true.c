#include <stdio.h>

int main(void)
{
    int i = 1,
        j = 0;

    if (i) {
        printf("true == %d\n", i);
    } else {
        printf("false == %d\n", i);
    }

    if (j) {
        printf("true == %d\n", j);
    } else {
        printf("false == %d\n", j);
    }

    return 0;
}
