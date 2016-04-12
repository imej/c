/* exercise 4-14 define a macro swap(t, x, y) that interchanges two arugments of type t*/
#include <stdio.h>

#define swap(T, A, B)  {T t = (A); \
                       (A) = (B);     \
		       (B) = t;}
int main(void) 
{
    int a = 3;
    int b = 4;
    swap(int, a, b);
    printf("a = %d\n", a);
    printf("b = %d\n", b);

    return 0;
}
