#include <stdio.h>

/*
 * Test how chars are stored in the memory
 */
int main()
{
    char chs[3];
    chs[0] = '1';
    chs[1] = '2';
    chs[2] = '3';

    int i = 0;
    for (i = 0; i < 3; i++) {
        printf("In the memory '%c' is saved as %#x.\n", chs[i], chs[i]);
    }
    return 0;
}
