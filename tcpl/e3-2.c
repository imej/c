/* exercise 3-2. escape */
#include <stdio.h>

#define MAXLEN 100

void escape(char s[], char t[]);

int main(void) 
{
    char t[] = "ASDasdf\tasdf\nsdf\nsdffffffff";
    char s[MAXLEN] = {0};
    escape(s, t);
    printf("%s\n", t);
    printf("%s\n", s);
    return 0;
}

void escape(char s[], char t[])
{
    int i, j;

    if (t != NULL && s != NULL) {
        for (i = 0, j = 0; t[i] != '\0'; i++) {
            switch (t[i]) {
                case '\n':
                    s[j++] = '\\';
		    s[j++] = 'n';
		    break;
		case '\t':
		    s[j++] = '\\';
		    s[j++] = 't';
		    break;
		default:
		    s[j++] = t[i];
            }
        }
	s[j] = '\0';
    } 
}
