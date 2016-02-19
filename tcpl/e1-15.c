/* convert F to C with a function*/
#include <stdio.h>

float F2C(float);

int main(void)
{
    float fahr;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    while (fahr <= upper) {
        printf("%3.0f %6.1f\n", fahr, F2C(fahr));
	fahr += step;
    }

    return 0;
}

float F2C(float fahr)
{
    return (5.0/9.0) * (fahr - 32.0);
}
