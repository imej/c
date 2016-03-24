/* Exercise 2-5 
   any(s1, s2) returns the first location in s1 where any character from s2 occurs,
   or -1 if s1 contains no characters from s2. */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int indexOf(char s[], char c);
int any(char s1[], char s2[]);

int main(void)
{
    char s1[] = "Hello, how are you doing!";
    char s2[] = "good";

    int i = any(s1, s2);
    printf("%s\n", s1);
    printf("%s\n", s2);
    printf("%d\n", i);
    
    return 0;
}

int indexOf(char s[], char c)
{
    int i, found;
    found = 0;
    for (i = 0; s[i] != '\0'; i++) {
        if (s[i] == c) {
	    found = 1;
	    break;
	}
    }

    if (!found) {
        return -1;
    } else {
        return i;
    }
}

int any(char s1[], char s2[])
{
    int i, j;
    for (i = 0; s1[i] != '\0'; i++) {
        j = indexOf(s2, s1[i]);
	if (j >= 0) {
	    return i;
	}
    }

    return -1;
}
