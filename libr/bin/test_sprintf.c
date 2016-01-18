#include <stdio.h>

int main(void) 
{
    char p[80];

    sprintf(p, "%#.*f", 5, 3.1415926);

    printf("%s\n", p);
    return 0;
}

