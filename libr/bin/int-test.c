#include <stdio.h>
/*
 * Test how the integers are stored in memory 
 */
union {
    unsigned short ms;
    unsigned char mc[2];
} myShort;

union {
    unsigned int mi;
    unsigned char mc[4];
} myInt;

int main()
{
    printf("sizeof(myShort) = %d.\n", sizeof(myShort));

    myShort.ms = 514;
    int i = 0;
    for (i = 0; i < 2; i++) {
        printf("myShort.mc[%d] = %#x\n", i, myShort.mc[i]);
    }
    
    printf("sizeof(myInt) = %d.\n", sizeof(myInt));

    myInt.mi = 32770;
    for (i = 0; i < 4; i++) {
        printf("myInt.mi[%d] = %#x\n", i, myInt.mc[i]);
    }

    return 0;
}
