/* exercise 5-5 strncpy, strncat, strncmp. */
#include <stdio.h>

int m_strncpy(char *, char *, int);
int m_strncat(char *, char *, int);
int m_strncmp(char *, char *, int);

int main(void) 
{
    char s[30];
    char t[] = "good";

    m_strncpy(s, t, 3);
    printf("%s\n", s);
    
    m_strncat(s, t, 2);
    printf("%s\n", s);

    printf("%d\n", m_strncmp(s, t, 2));
    printf("%d\n", m_strncmp(s, t, 4));

    return 0;
}

int m_strncpy(char *s, char *t, int n)
{
    int i;

    for (i = 0; i < n && *(t+i) != '\0'; i++) {
        *(s+i) = *(t+i);
    }

    while (i < n) {  /* fill null if not long enough */
        *(s+i) = '\0';
	i++;
    }

    *(s+n) = '\0';

    return n;
}

int m_strncat(char *s, char *t, int n)
{
    int i, j;

    for (i = 0; *(s+i) != '\0'; i++) {
        ;
    }

    for (j = 0; j < n && *(t+j) != '\0'; j++) {
        *(s+i+j) = *(t+j);
    }

    return j;
}

int m_strncmp(char *s, char *t, int n)
{
    int i;

    for (i = 0; *(s+i) == *(t+i) && *(s+i) != '\0' && *(t+i) != '\0' && i < n; i++) {
        ;
    }

    if (i == n) {
        return 0;
    }

    return *(s+i) - *(t+i);
}
