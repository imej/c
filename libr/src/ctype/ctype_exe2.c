#include <stdio.h>
#include "ctype_r.h"

size_t idlen(const char *s)
{
    size_t rc = 0;
    int i = 0;

    if (s != NULL) {
        while ((char)*(s+i) != '\0') {
	    if (isalnum((char)*(s+i)) || (char)*(s+1) == '_') {
	        rc++;
	    }
	    
	    i++;
	}    
    }

    return rc;
}

int main()
{
    char *s = "Hello, world";
    printf("%u\n", idlen(s));
    return 0;
}

