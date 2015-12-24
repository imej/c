#include <stdio.h>
/*
 * How to use arrays of funciton pointers.
 */

float Plus     (float a, float b) {return a + b;}
float Minus    (float a, float b) {return a - b;}
float Multiply (float a, float b) {return a * b;}
float Divide   (float a, float b) {return a / b;}

typedef float (*pt2Func)(float, float);

int main()
{
    float a = 5.0;
    float b = 2.0;

    /* Delcare a function pointer array declared with typedef. */
    pt2Func funcArray1[4] = {NULL};
    funcArray1[0] = &Plus;
    funcArray1[1] = &Minus;
    funcArray1[2] = &Multiply;
    funcArray1[3] = &Divide;
    
    printf("typedef function pointer array: %f + %f = %f\n", a, b, funcArray1[0](a, b));
    printf("typedef function pointer array: %f - %f = %f\n", a, b, (*funcArray1[1])(a, b));
    printf("typedef function pointer array: %f * %f = %f\n", a, b, (*funcArray1[2])(a, b));
    printf("typedef function pointer array: %f / %f = %f\n", a, b, (*funcArray1[3])(a, b));

    /* Delcare a function pointer array directly.*/
    float (*pt2Dir[4])(float, float) = {NULL};
    pt2Dir[0] = &Plus;
    pt2Dir[1] = &Minus;
    pt2Dir[2] = &Multiply;
    pt2Dir[3] = &Divide;

    printf("direct function pointer array: %f + %f = %f\n", a, b, pt2Dir[0](a, b));
    printf("direct function pointer array: %f - %f = %f\n", a, b, (*pt2Dir[1])(a, b));
    printf("direct function pointer array: %f * %f = %f\n", a, b, (*pt2Dir[2])(a, b));
    printf("direct function pointer array: %f / %f = %f\n", a, b, pt2Dir[3](a, b));

    return 0;
}
