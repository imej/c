/* exercise 4-13 recursive version of function reverse(s) */
#include <stdio.h>
#include <string.h>

void reverse(char s[], int, int);

int main(void) 
{
    char s[] = "Hello!";
    reverse(s, 0, strlen(s) -1 );
    printf("Reversed: %s\n", s);
    return 0;
}

/* reverse: reverse string s in place */
void reverse(char s[], int start, int end)
{
    char c;
    if (end > start) {
        c = s[start];
	s[start] = s[end];
	s[end] = c;

	if (end > start + 2) {
	    reverse(s, start + 1, end -1);
	}
    } 
}
