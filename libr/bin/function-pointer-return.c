#include <stdio.h>
/*
 * Two formats to return a function pointer from a function:
 */

float Plus     (float a, float b) {return a + b;}
float Minus    (float a, float b) {return a - b;}
float Multiply (float a, float b) {return a * b;}
float Divide   (float a, float b) {return a / b;}

/* Pay attention to the 3 'float' in the function declaration. They indicate
 * what the returned function looks like: it takes two floats as parameters, 
 * and returns one float
 */
float (*GetPtr1(const char opCode))(float, float)
{
    if (opCode == '+') {
        return &Plus;
    } else {
        return &Minus;
    }
}

/* Use a typedef. It looks better? */
typedef float (*typep)(float, float); 
typep GetPtr2(const char opCode)
{
    if (opCode == '+') {
        return &Plus;
    } else {
        return &Minus;
    }
}

int main()
{
    float a = 5.0;
    float b = 2.0;
    
    /* declare a funtion pointer. */
    float (*pt2Func)(float, float) = NULL;

    pt2Func = GetPtr1('+');
    printf("GetPtr1: %f + %f = %f\n", a, b, pt2Func(a, b));

    pt2Func = GetPtr2('-');
    printf("GetPtr2: %f - %f = %f\n", a, b, pt2Func(a, b));

    return 0;
}
