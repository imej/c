#include <stdio.h>
/*
 * Test how the floats are stored in memory 
 */
union {
    float mf;
    unsigned char mc[4];
} myFloat;
/*
union {
    unsigned int mi;
    unsigned char mc[4];
} myInt;
*/
int main()
{
    // printf("sizeof(myFloat) = %d.\n", sizeof(myFloat));

    myFloat.mf = 1025;
    int i = 0;
    for (i = 3; i > -1; i--) {
        printf("%#x|", myFloat.mc[i]);
    }
    printf("\t%f\n", myFloat.mf);
/*    
    printf("sizeof(myInt) = %d.\n", sizeof(myInt));

    myInt.mi = 32770;
    for (i = 3; i > -1; i--) {
        printf("myInt.mi[%d] = %#x\t", i, myInt.mc[i]);
    }

    printf("------------------------------------------------\n");
*/
    return 0;
}
