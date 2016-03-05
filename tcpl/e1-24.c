/* I check a C program for rudimentary syntax errors: 
   - unbalanced parentheses, brackets and braces */
#include <stdio.h>
#include <stdlib.h>

#define MAXLINE 1000
enum OpenSymbol {
    PR,  /* Parenthese */
    BK,  /* Bracket */
    BA,  /* Brace */
    SQ,  /* Single Quote */
    DQ,  /* Double Quote */
    CM  /* Comments */
};

typedef struct MyStack {
    enum OpenSymbol os;
    int lineNo;
    struct MyStack *previous;
} MyStack;



int catchline(char line[], int maxline);
void copy(char to[], char from[]);
int removeComments(char from[], char to[], int len, int *inCom);

int main(void)
{
    int i;
    int len;  /* length of the current line */
    int max;  /* maximum length of the lines that have been read */
    int cl;   /* length of one time read. <= MAXLINE */
    char *line;   /* current line */
    char *noComm;   /* comments removed */
    char *ost;  /* the output sting - includes all lines that are longer than 80 chars */
    char *buf;      /* current reading (one time) */

    int ic = 0;  /* in comments mark 0 - false, 1 - true */

    max = 0;
    len = 0;

    /* initialize buffer to be MAXLINE */
    buf = calloc(MAXLINE, sizeof(char));
    line = calloc(MAXLINE, sizeof(char));
    noComm = calloc(MAXLINE, sizeof(char));
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

        if (len > MAXLINE) {
	    noComm = realloc(noComm, len * sizeof(char));
	}

        len = removeComments(line, noComm, len, &ic);

        if (len > 0) {
	    max += len;
	    if (max > MAXLINE) {
	        ost = realloc(ost, max * sizeof(char));
	    }
	    copy(&ost[max-len], noComm);
	}
    }

    if (max > 0) {
        printf("%s", ost);
    }

    free(buf);
    free(line);
    free(noComm);
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

int removeComments(char from[], char to[], int len, int *inCom)
{
    int oq = 0;  /* open quotation mark 0 - false, 1 - true */
    int i = 0;
    int j = 0;

    while (from[i] != '\0') {
        if (*(inCom) || (!oq && from[i] == '/' && from[i+1] == '*')) {
	    /* we are in comments. */
	    if (from[i] == '*' && from[i+1] == '/') {
	        /* comments end */
		*inCom = 0;
		i = i + 2;
	    } else {
	        if (*inCom == 0) {
		    *inCom = 1;
		}
	        i++;
	    }    
	} else {
	    /* we are not in comments */
            to[j++] = from[i++];

	    if (from[i] != '\'' && from[i-1] == '\"') {
	        /* open quotation */
		oq = (oq + 1) % 2;
	    }
	}
    }

    to[j] = '\0';

    return j;
}
