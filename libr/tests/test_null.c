#include <stdio.h>
#define X 0xe000

int main(void)
{
    unsigned short msh1 = 0x00;
    unsigned short msh2 = X|0x00;
    unsigned short msh3 = X;
    unsigned short ma[1] = {X};


    printf("X = %d\n", X);
    printf("msh1 = %d\n", msh1);
    printf("msh2 = %d\n", msh2);
    printf("msh3 = %d\n", msh3);
    if ((void *)msh3 == NULL) {
        printf("msh3 is NULL pointer.\n");
    } else {
        printf("msh3 is not  NULL pointer.\n");
    }
    if (ma[0] == NULL) {
        printf("ma[0] is NULL pointer.\n");
    } else {
        printf("ma[0] is not  NULL pointer.\n");
    }

    return 0;
}
