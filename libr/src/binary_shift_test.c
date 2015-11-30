#include <stdio.h>

int main()
{
    int i = 0;
    for (i = 0; i < 12; i++) {
        printf("%d\n", (1 << i));
    }

    return 0;
}
