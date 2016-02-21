/* print all input lines that are longer than 80 characters.
   use a big string to hold all the output. */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define HOLD 80

int catchline(char line[], int maxline);
void copy(char to[], char from[]);

int main(void)
{
    int i;
    int len;  /* length of the current line */
    int max;  /* maximum length of the lines that have been read */
    int cl;   /* length of one time read. <= MAXLINE */
    char *line;   /* current line */
    char *ost;  /* the output sting - includes all lines that are longer than 80 chars */
    char *buf;      /* current reading (one time) */

    max = 0;
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

        if (len > HOLD) {
	    max += len;
	    if (max > MAXLINE) {
	        ost = realloc(ost, max * sizeof(char));
	    }
	    copy(&ost[max-len], line);
	}
    }

    if (max > 0) {
        printf("%s", ost);
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
