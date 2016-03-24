/* an alternate version of squeeze(s1, s2) that 
   deletes each character in s1 that matches any character in s2.*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void squeeze(char s[], int c);
void squeezeAll(char s1[], char s2[]); 

int main(void)
{
    char s1[] = "Hello, how are you doing!";
    char s2[] = "good";

    printf("%s - %s = ", s1, s2);

    squeezeAll(s1, s2);

    printf("%s\n", s1);
    
    return 0;
}

/* squeeze: delete all c from s */
void squeeze(char s[], int c)
{
    int i, j;

    for (i = j = 0; s[i] != '\0'; i++) 
        if (s[i] != c)
	    s[j++] = s[i];
    s[j] = '\0';
}

/*sqeezeAll: delete all chars in s2 from s1 */
void squeezeAll(char s1[], char s2[]) 
{
    int i;

    for (i = 0; s2[i] != '\0'; i++) {
        squeeze(s1, s2[i]);
    }
}
