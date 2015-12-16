#include <stdio.h>
/*
 * Test how a floating point number is stored in memory:
 *
 * SEEEEEEEEMMMMMMMMMMMMMMMMMMMMMMM
 *
 * S - sign: 0 positive, 1 nagitive
 * E - Exponent = what number that is expressed by the pattern - 127
 * M - Mantissa: 1st position means 1/2, 2nd 1/4, 1/8 ...... there is a implied 1 to be added.
 * The value = (sign)2^exponent * mantissa
 */
union {
    float mf;
    unsigned char mc[4];
} my[10];

int main()
{
    my[0].mf = 2048;
    my[1].mf = 2049;
    my[2].mf = 2050;
    my[3].mf = 2051;
    my[4].mf = 2052;
    my[5].mf = 2053;
    my[6].mf = 2054;
    my[7].mf = 2055;
    my[8].mf = 2056;
    my[9].mf = 2057;

    int i = 0;
    int j = 0;
    for (j = 0; j < 10; j++) {
        for (i = 3; i > -1; i--) {
            printf("%#x|", my[j].mc[i]);
        }
        printf("\t%f\n", my[j].mf);
    }

    return 0;
}
