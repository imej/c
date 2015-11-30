#include <stdio.h>
#include "ctype_r.h"

#define istype(A, B, C)                                        \
    if (B(A)) {                                                \
         (C) > 0 ? printf(", %s", #B) : printf("%s", #B);      \
	 (C)++;                                                \
    }

int main()
{
    char *str = "Hello, world!\n";
    int i = 0, j = 0;

    while (*(str + i) != '\0') {
        *(str + i) == '\n' ? printf("CR: ") : printf("%c: ", *(str+i));
	
	istype(*(str + i), isalnum, j)
	istype(*(str + i), isalpha, j)
	istype(*(str + i), iscntrl, j)
	istype(*(str + i), isdigit, j)
        istype(*(str + i), isgraph, j)
	istype(*(str + i), islower, j)
	istype(*(str + i), isprint, j)
	istype(*(str + i), ispunct, j)
	istype(*(str + i), isspace, j)
	istype(*(str + i), isxdigit, j)
	istype(*(str + i), isupper, j)

	printf("\n");
	i++;
	j = 0;
     }

    return 0;
}

