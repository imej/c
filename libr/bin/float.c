#include <stdio.h>

typedef union {
    float _D;
    unsigned short _Us[2];
} dmax;

int main()
{
     printf("sizeof(unsigned char) = %d\n", sizeof(unsigned char));
     printf("sizeof(unsigned short) = %d\n", sizeof(unsigned short));
     printf("sizeof(float) = %d\n", sizeof(float));
     printf("sizeof(dmax) = %d\n", sizeof(dmax));

    dmax dm = {100.0};

    int i = 0;
    for (i = 0; i < 2; i++) {
        printf("_Us[%d] = %#x\n", i, dm._Us[i]);
    }

    return 0;
}
