#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char *_Defloc(void);

int main(void)
{
    char *p = (char *)_Defloc();

    if (p != NULL) {
        printf("My default locale is: %s\n", p);
	if (strcmp(p, "C") != 0) {
	    free(p);
	}
    } else {
        printf("Cannot find my default locale.");
    }
   
    return 0;
}
