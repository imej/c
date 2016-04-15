#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAXLINES 5000       /* max #lines to be sorted */

char *lineptr[MAXLINES];      /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void qsort(char *lineptr[], int left, int right);
size_t getTime(char *ct, size_t ctlen); 

/* sort input lines */
int main(void)
{
    char buf[80];

    int nlines;   /* number of input lines read */

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        getTime(buf, 80);
	printf("Sorting start: %s\n",buf);
        qsort(lineptr, 0, nlines-1);
	writelines(lineptr, nlines);
	return 0;
    } else {
        printf("error: input too big to sort\n");
	return 1;
    }
}

#define MAXLEN 1000    /* max length of any input line */
int catchline(char *, int);
char *alloc(int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = catchline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = alloc(len)) == NULL) {
	    return -1;
	} else {
	    line[len-1] = '\0'; /* delete new line */
	    strcpy(p, line);
	    lineptr[nlines++] = p;
	}
    }

    return nlines;
}

/* writelines: write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++) {
        printf("%s\n", lineptr[i]);
    }
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

/* qsort: sort v[left]...v[right] into increasing order */
void qsort(char *v[], int left, int right)
{
    int i, last;
    void swap(char *v[], int i, int j);

    if (left >= right)   /* do nothing if array contains */
        return ;         /* fewer than two elments */
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i<= right; i++)
        if (strcmp(v[i], v[left]) < 0)
	    swap(v, ++last, i);
    swap(v, left, last);
    qsort(v, left, last-1);
    qsort(v, last+1, right);
}

/*swap: interchange v[i] and v[j] */
void swap(char *v[], int i, int j)
{
    char *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#define ALLOCSIZE 10000 /* size of available space */

static char allocbuf[ALLOCSIZE];     /* storage for alloc */
static char *allocp = allocbuf;      /* next free position */

char *alloc(int n)          /* return pointer to n characters */
{
    if (allocbuf + ALLOCSIZE - allocp >= n) {
        /* it fits */
	allocp += n;
	return allocp - n;  /* old p */
    } else {
        /* not enough room */
	return 0;
    }
}

void afree(char *p)   
{
    /* free storage pointed to by p */
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
}

/* Current system time */
size_t getTime(char *ct, size_t ctlen) 
{
    time_t now = time(NULL);
    struct tm *ts = localtime(&now);

    return strftime(ct, ctlen, "%a %Y-%m-%d %H:%M:%S %Z", ts);
}
