/* exercise 3-3. expand */
#include <stdio.h>

#define MAXLEN 100

void expand(char s[], char t[]);

int main(void) 
{
    char t[] = "---ASDasdfg-p-wasdfsdf2-9sd-Qffffffff---";
    char s[MAXLEN] = {0};
    expand(s, t);
    printf("%s\n", t);
    printf("%s\n", s);
    return 0;
}

void expand(char s[], char t[])
{
    int i, j, k;

    if (t != NULL && s != NULL) {
        for (i = 0, j = 0; t[i] != '\0'; i++) {
	    if (t[i] == '-' && i != 0 && t[i+1] != '\0') {
	        if (t[i-1] >= 'a' && t[i-1] <'z' && t[i+1] - t[i-1] > 0 && t[i+1] - t[i-1] < 26) {
		    for (k = 1; k <= t[i+1] - t[i-1]; k++) {
		        s[j++] = t[i-1] + k;
		    }
		    i++;
		} else if (t[i-1] >= 'A' && t[i-1] <'Z' && t[i+1] - t[i-1] > 0 && t[i+1] - t[i-1] < 26) {
		    for (k = 1; k <= t[i+1] - t[i-1]; k++) {
		        s[j++] = t[i-1] + k;
		    }
		    i++;
		} else if (t[i-1] >= '0' && t[i-1] <'9' && t[i+1] - t[i-1] > 0 && t[i+1] - t[i-1] < 10) {
		    for (k = 1; k <= t[i+1] - t[i-1]; k++) {
		        s[j++] = t[i-1] + k;
		    }
		    i++;
		} else {
		    s[j++] = t[i];
		}
	    } else {
	        s[j++] = t[i];
	    }
        }
	s[j] = '\0';
    } 
}
