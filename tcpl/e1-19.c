/* reverse character string */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000

int catchline(char line[], int maxline);
void copy(char to[], char from[]);
void reverse(char to[], char from[]);

int main(void)
{
    int i;
    int len;  /* length of the current line */
    int cl;   /* length of one time read. <= MAXLINE */
    char *line;   /* current line */
    char *ost;  /* the output sting - includes all lines that are longer than 80 chars */
    char *buf;      /* current reading (one time) */

    len = 0;

    /* initialize buffer to be MAXLINE */
    buf = calloc(MAXLINE, sizeof(char));
    line = calloc(MAXLINE, sizeof(char));
    ost = calloc(MAXLINE, sizeof(char));

    while ((cl = catchline(buf, MAXLINE)) > 0) {
        copy(line, buf);
	len = cl;
        if (cl == MAXLINE - 1 && buf[MAXLINE - 2] != '\n') {
	    /* more need to read */
	    i = 1;
	    while ((cl = catchline(buf, MAXLINE)) > 0) {
	        line = realloc(line, (++i) * MAXLINE * sizeof(char));
	        copy(&line[len], buf);
	        len = len + cl;

		if (buf[cl - 1] == '\n') {
		    break;
		}
	    }
	}

        if (len > 0) {
	    if (len > MAXLINE) {
	        ost = realloc(ost, len * sizeof(char));
	    }
	    reverse(ost, line);
            printf("%s", ost);
	}
    }

    free(buf);
    free(line);
    free(ost);

    return 0;
}

int catchline(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c!= '\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
	++i;
    }

    s[i] = '\0';
    return i;
}

void copy(char to[], char from[])
{
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0') {
        ++i;
    }
}

void reverse(char to[], char from[])
{
    /* reverse the characters */
    int i, ub, flag;
    for (ub = 0; from[ub] != '\0'; ub++) {
        
    }

    flag = 0;
    if (from[ub-1] == '\n') {
        flag = 1;
	ub--;
    }

    i = 0;
    for (; ub > 0; ub--, i++) {
        to[i] = from[ub-1]; 
    }

    if (flag) {
        to[i++] = '\n';
    }
    to[i] = '\0';
}
