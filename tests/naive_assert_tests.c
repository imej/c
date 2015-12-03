#include <stdio.h>

#define assert(test) if (!(test))                                   \
    fprintf(stderr, "Assertion failed: %s, file %s, line %i\n",     \
            #test, __FILE__, __LINE__)

int main() 
{
    assert(1 == 2);
    return 0;
}
