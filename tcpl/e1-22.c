/* "fold" long input lines into two or more short lines
   after the last non-blank character that occurs before 
   the n-th column of input. */
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define FOLDNUM 10

int catchline(char line[], int maxline);
void copy(char to[], char from[]);
char *fold(char str[]);

int main(void)
{
    int i;
    int len;  /* length of the current line */
    int max;  /* maximum length of the lines that have been read */
    int cl;   /* length of one time read. <= MAXLINE */
    char *line;   /* current line */
    char *buf;      /* current reading (one time) */

    max = 0;
    len = 0;

    /* initialize buffer to be MAXLINE */
    buf = calloc(MAXLINE, sizeof(char));
    line = calloc(MAXLINE, sizeof(char));

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
        printf("%s",fold(line));
    }

    free(buf);
    free(line);

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

char *fold(char str[])
{
    int len, hasEmpty;
    int i = 0;

    hasEmpty = 0;
    for (len = 0; str[len] != '\0'; len++) {
        if (str[len] == ' ' || str[len] == '\t') {
	    hasEmpty = len;
	}
    }

    if (hasEmpty >= FOLDNUM) { /* need to fold */
        while (str[i] != '\0' && i < len - FOLDNUM) {
	    i += FOLDNUM;
	    while (str[i] != '\0') {
	        i++;
	        if (str[i-1] == ' ' || str[i-1] == '\t') {
		    str[i-1] = '\n';
		    break;
		}
	    }
	}
        
    }
   
    return str;
}
