/* exercise 5-3 strcat - pointer version */
#include <stdio.h>

void m_strcat(char *s, char *t);

int main(void) 
{
    char s[30] = "Hello";
    char t[] = "world!";

    m_strcat(s, t);

    printf("%s\n", s);
    return 0;
}

/* pointer version of strcat. It copies the string t to the end of s. */
void m_strcat(char *s, char *t)
{
    char *p = s;
    while (*p != '\0') {
        p++; 
    }
    while ((*(p++) = *(t++)) != '\0')
        ;
}
