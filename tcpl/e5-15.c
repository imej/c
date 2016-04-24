/* e5-15: -f to fold upper and lower case together */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXLINES 5000    /* max #lines to be sorted */
char *lineptr[MAXLINES]; /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

void mqsort(void *lineptr[], int left, int right, 
           int (*comp)(void *, void *));
int numcmp(char *, char *);
void reverseF(void *v[], int len) ;
void upper(char *str1);
int strcmp_ignoreCase(const char *str1, const char *str2);

/* sort input lines */
int main(int argc, char *argv[])
{
    int i, j, c, nlines;         /* number of input lines read */
    int numeric = 0;             /* 1 if numeric sort */
    int reverse = 0;             /* 1 if decreasing sort*/
    int foldul = 0;              /* 1 fold upper and lower case together */
    for (i = 1; i < argc; i++) {
        if ((*++argv)[0] == '-') {
	    for (j = 1; (c = (*argv)[j]) != '\0'; j++) {
	        switch (c) {
		    case 'n':
		        numeric = 1;
			break;
		    case 'r':
		        reverse = 1;
			break;
		    case 'f':
		        foldul = 1;
			break;
		}
	    }
	}
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0) {
        if (numeric) {
            mqsort((void **) lineptr, 0, nlines-1, 
	        (int (*) (void *, void *))numcmp);
	} else if (foldul) {
            mqsort((void **) lineptr, 0, nlines-1, 
	        (int (*) (void *, void *))strcmp_ignoreCase);
	} else {
            mqsort((void **) lineptr, 0, nlines-1, 
	        (int (*) (void *, void *))strcmp);
	}

        if (reverse) {
	    reverseF((void **)lineptr, nlines);
	}

	writelines(lineptr, nlines);

	for (i = 0; i < nlines; i++) {
	    if (lineptr[i] != NULL) {
	        free(lineptr[i]);
	    }
	}
	return 0;
    } else {
        printf("input too big to sort\n");
	return 1;
    }
}

/* mqsort: sort v[left]...v[right] into increasing order */
void mqsort(void *v[], int left, int right,
           int (*comp) (void *, void *))
{
    int i, last;
    void swap(void *v[], int, int);

    if (left >= right) {  /* do nothing if array contains */
        return;           /* fewer than two elements */
    }

    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i++) {
        if ((*comp)(v[i], v[left]) < 0) {
	    swap(v, ++last, i);
	}
    }

    swap(v, left, last);
    mqsort(v, left, last-1, comp);
    mqsort(v, last+1, right, comp);
}

/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    return atof(s1) - atof(s2);
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

#define MAXLEN 1000    /* max length of any input line */
int catchline(char *, int);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = catchline(line, MAXLEN)) > 0) {
        if (nlines >= maxlines || (p = malloc(len)) == NULL) { /* alloc => malloc*/
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

void reverseF(void *v[], int len) 
{
    int i;
    
    for (i = 0; i+1 < len; i++, len--) {
        swap(v, i, len-1);
    }
    
}

void upper(char *str1)
{
    int i;
    if (str1 != NULL) {
        for (i = 0; *(str1+i) != '\0'; i++) {
	    *(str1+i) = toupper(*(str1+i));
	}
    }
}

int strcmp_ignoreCase(const char *str1, const char *str2)
{
    char ustr1[MAXLEN], ustr2[MAXLEN];

    strcpy(ustr1, str1);
    upper(ustr1);

    strcpy(ustr2, str2);
    upper(ustr2);

    return strcmp(ustr1, ustr2);
}
