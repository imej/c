#include <stdio.h>
/*
 * Function pointers can be declared:
 * 1) dateType (*pointerName)(parameters)
 * 2) typedef dateType pointerName(parameters)
 *
 * Pointers that have been declared either way can be called:
 *     pointerName(parameters)
 * 
 * Compiler ensures that only a function accepts the exact parameter(s) and returns
 * the exact date type can be assigned to a function pointer.
 *
 * &functionName is the address of a function and it can be passed to a function
 * pointer.
 *
 */
typedef float typep(float, float);

float Plus     (float a, float b) {return a + b;}
float Minus    (float a, float b) {return a - b;}
float Multiply (float a, float b) {return a * b;}
float Divide   (float a, float b) {return a / b;}

float Switch(float a, float b, char opCode)
{
    float result;

    switch(opCode) {
        case '+' : result = Plus     (a, b); break;
        case '-' : result = Minus    (a, b); break;
        case '*' : result = Multiply (a, b); break;
        case '/' : result = Divide   (a, b); break;
    }

    return result;
}

float Function_Pointer(float a, float b, float (*ptbFunc)(float, float))
{
    float result = ptbFunc(a, b);

    return result;
}

float Typedef_Pointer(float a, float b, typep func)
{
    float result = func(a, b);

    return result;
}

int main()
{
    float a = 5;
    float b = 2;

    printf("Switch: %f + %f = %f\n", a, b, Switch(a, b, '+'));
    printf("Switch: %f - %f = %f\n", a, b, Switch(a, b, '-'));
    printf("Switch: %f * %f = %f\n", a, b, Switch(a, b, '*'));
    printf("Switch: %f / %f = %f\n", a, b, Switch(a, b, '/'));
    printf("Function_Pointer: %f + %f = %f\n", a, b, Function_Pointer(a, b, &Plus));
    printf("Function_Pointer: %f - %f = %f\n", a, b, Function_Pointer(a, b, &Minus));
    printf("Function_Pointer: %f * %f = %f\n", a, b, Function_Pointer(a, b, &Multiply));
    printf("Function_Pointer: %f / %f = %f\n", a, b, Function_Pointer(a, b, &Divide));
    printf("Typedef_Pointer: %f + %f = %f\n", a, b, Typedef_Pointer(a, b, &Plus));
    printf("Typedef_Pointer: %f - %f = %f\n", a, b, Typedef_Pointer(a, b, &Minus));
    printf("Typedef_Pointer: %f * %f = %f\n", a, b, Typedef_Pointer(a, b, &Multiply));
    printf("Typedef_Pointer: %f / %f = %f\n", a, b, Typedef_Pointer(a, b, &Divide));

    return 0;
}
