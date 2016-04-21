/* 5-13. tail -n displays the last n lines of the user input */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 500000       /* max #lines to be sorted */
#define MAXLEN 5000           /* max characters in a line */
#define DEFAULTTAIL 10

int catchline(char s[], int lim);
void m_tail(int maxlines);

int main(int argc, char *argv[])
{
    int wantedlen; /* user entered line number */

    if (argc > 1 && (*++argv)[0] == '-') {
        wantedlen = atoi(&(*argv)[1]);
    } else {
        wantedlen = DEFAULTTAIL;
    }

    printf("wantedlen = %d\n", wantedlen);

    m_tail(wantedlen);

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

/* m_tail: get the last n lines of the input maxlines = n */
void m_tail(int maxlines)
{
    int i, len, nlines;
    char line[MAXLEN];

    char *lineptr[MAXLINES] = {0};      /* pointers to text lines */

    nlines = 0;
    while ((len = catchline(line, MAXLEN)) > 0) {
        line[len-1] = '\0';  /* delete new line char */

        if (lineptr[nlines] != NULL) {
	    free(lineptr[nlines]);
	} 
        lineptr[nlines] = malloc(len);
	
	if (lineptr[nlines] == NULL) {
	    printf("no memory!\n");
	}

	strcpy(lineptr[nlines++], line);
	nlines %= maxlines;
    }

    if (lineptr[nlines] == NULL) {
        /* no enough lines to return */
	for (i = 0; i < nlines; i++) {
	    printf("%s\n", lineptr[i]);
	}
    } else {
        /* lineptr[nlines] holds the first line */
        for (i = 0; i < maxlines; i++) {
	    printf("%s\n", lineptr[nlines++]);
	    if (nlines == maxlines) {
	        nlines = 0;
	    }
	}
    }

    for (i = 0; i < maxlines; i++) {
	if (lineptr[i] != NULL)
	    free(lineptr[i]);
    }
}
