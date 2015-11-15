#include <stdio.h>

#define Testclaim(assertion, returnval) if (!(assertion))    \
           {fprintf(stderr, #assertion "failed to be true.   \
	   Returning" #returnval "\n"); return returnval;}

int main() 
{
    int x = 0, y = 1;
    Testclaim(x == y, -1);
    return 0;
}
