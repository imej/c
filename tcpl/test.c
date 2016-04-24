#include <stdio.h>
#include <ctype.h>

void upper(char *str1);

int main(void)
{
    char str[] = "Hello, world!";
    upper(str);

    printf("%s\n", str);
    return 0;
}

void upper(char *str1)
{
    int i;
    if (str1 != NULL) {
        for (i = 0; *(str1+i) != '\0'; i++) {
	    *(str1+i) = toupper(*(str1+i));
	}
    }
}

