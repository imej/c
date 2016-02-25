/* entab - replaces strings of blanks by the minimum number of tabs 
   and blanks to achieve the same spacing. */

#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
#define SUBCHAR '\t'
#define SUBBLOCKS 4

int catchline(char line[], int maxline);
void copy(char to[], char from[]);
void entab(char to[], char from[]);

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
            entab(ost, line);
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

void entab(char to[], char from[])
{
    /* replace \t with something else */
    int tc = 0; /* tab count */
    int sc = 0; /* space count */
    int i = 0;
    int j, k;

    /* find the length of from, in case we need to increase to */
    while (from != NULL && from[i] != '\0') {
	i++;
    }

    if (i > MAXLINE) {
        to = realloc(to, i * sizeof(char) + 1);
    }

    i = 0; 
    j = 0; 
    while (from[i] != '\0') {
        if (from[i] == ' ') {
	    sc++;
	    i++;
	} else {
	    if (sc > 0) {
	        tc = sc / SUBBLOCKS;
		sc = sc % SUBBLOCKS;
                for (k = 0; k < tc; k++) {
		    to[j++] = SUBCHAR;
		}

		for (k = 0; k < sc; k++) {
		    to[j++] = ' ';
		}
		sc = 0;
	    } else {
	        to[j++] = from[i++];
	    }
	}
    }

    to[j] = '\0';
}
