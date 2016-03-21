/* I check a C program for rudimentary syntax errors: 
   - unbalanced parentheses, brackets and braces 
   RULES:
   1. Closing characters must be the same type as the most recent openning characters.
      Except in comments or between " or '.
   2. C comments do not nest.
   3. Anything can appear between "s
   4. Parentheses, brackets, single/doulbe quotes cannot across lines
   5. Things can appear between 's:
       - Single characters
       - escapes: \a, \b, \f, \n, \r, \t, \v, \\, \', \", \?
                  \nnn (n = 0-7)
		  \xhh (h = 0-9, a-f, A-F) 
 */
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

MyStack *Init_MyStack(enum OpenSymbol opsym, int ln, MyStack *preMS)
{
    MyStack *p = malloc(sizeof(MyStack));

    if (p != NULL) {
        p->os = opsym;
	p->lineNo = ln;
	p->previous = preMS;
    }

    return p;
}

MyStack *Destroy_MyStack(MyStack *p)
{
    if (p != NULL) {
        MyStack *pre = p->previous;
        free(p);
	return pre;
    } else {
        return NULL;
    }
}

void Destroy_All(MyStack *p)
{
    while (p != NULL) {
        p = Destroy_MyStack(p);
    }
}

int catchline(char line[], int maxline);
void copy(char to[], char from[]);
int isValidChar(char *arg);
int checkChar(char line[], int from);
int checkString(char line[], int from); 
int checkComments(char line[], int from, int *ic);

int main(void)
{
    int i, j;
    int len;  /* length of the current line */
    int cl;   /* length of one time read. <= MAXLINE */
    int ln = 0;  /* line number */
    char *line;   /* current line */
    char *buf;      /* current reading (one time) */
    int steps;
    MyStack *ms = NULL;
    MyStack *tmpMs;
    char c;

    int ic = 0;  /* in comments mark 0 - false, 1 - true */

    len = 0;

    /* initialize buffer to be MAXLINE */
    buf = calloc(MAXLINE, sizeof(char));
    line = calloc(MAXLINE, sizeof(char));

    while ((cl = catchline(buf, MAXLINE)) > 0) {
        ln++;
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

        j = 0;
	/* jump over comments */
	while (ic && line[j] != '\0') {
	    if (line[j] == '*' && line[j+1] == '/') {
	        ic = 0;
	        j += 2;
		break;
	    } else {
	        j++;
	    } 
	}

	while (line[j] != '\0') {
	    switch (line[j]) {
	        case '\"': /* first, skip string */
		    steps = checkString(line, j);
		    if (steps < 0) {
		        printf("Error in line %d around \".\n", ln);
			goto ex;
		    } else {
		        j = j + steps + 1;
		    }
		    break;
   
                case '\'': /* skip char */
		    steps = checkChar(line, j);
		    if (steps < 0) {
		        printf("Error in line %d around \'.\n", ln);
			goto ex;
		    } else {
		        j = j + steps + 1;
		    }
                    
		    break;

		case '/': /* check comments */
                    steps = checkComments(line, j, &ic);
		    if (steps >= 0) { 
		        j = j + steps + 1;
		    } else { /* not a comment */
		        j++;
		    } 

		    break;

		case '(': /* parenthese starts */
                    tmpMs = Init_MyStack(PR, ln, ms);
		    ms = tmpMs;
		    j++;
		    break;

		case '[': /* bracket starts */
                    tmpMs = Init_MyStack(BK, ln, ms);
		    ms = tmpMs;
		    j++;
		    break;

		case '{': /* brace starts */
                    tmpMs = Init_MyStack(BA, ln, ms);
		    ms = tmpMs;
		    j++;
		    break;

		case ')': /* close parenthese */
		    if (ms == NULL) {
		        printf("Error in line %d - ) without (.", ln);
			goto ex;
		    } else {
                        if (ms->os == PR) {
		            ms = Destroy_MyStack(ms);
			    j++;
		        } else {
		            goto unclose;
		        }
		    }
		    break;

		case ']': /* close parenthese */
		    if (ms == NULL) {
		        printf("Error in line %d - ] without [.", ln);
			goto ex;
		    } else {
                        if (ms->os == BK) {
		            ms = Destroy_MyStack(ms);
			    j++;
		        } else {
		            goto unclose;
		        }
		    }
		    break;

		case '}': /* close parenthese */
		    if (ms == NULL) {
		        printf("Error in line %d - } without {.", ln);
			goto ex;
		    } else {
                        if (ms->os == BA) {
		            ms = Destroy_MyStack(ms);
			    j++;
		        } else {
		            goto unclose;
		        }
		    }
		    break;

		default: 
		    j++;
		    break;
	    }
	}

    }

    /* make sure comments are closed */
    if (ic) {
        printf("Reached the end of the file while comments are not closed.\n");
    }

unclose:    
    if (ms != NULL) {
        switch (ms->os) {
	    case PR:
	        c = '(';
		break;
            case BK:
	        c = '[';
		break;
	    case BA:
	        c = '{';
		break;
	    default:
	        c = '!';
		break;
	}
        printf("Error in line %d, %c is not closed.\n", ms->lineNo, c);
    }

ex:
    free(buf);
    free(line);
    if (ms != NULL) {
        Destroy_All(ms);
    }
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

int isValidChar(char *arg)
{
    /* check if the parameter (C string - ends with \0) includes (starts) a char expression.
       1. start and end with '
       2. a single character that is not ', ", \, ?
       3. two characters that are \a, \b, \f, \n, \r, \t, \v, \\, \', \", \?
       4. four characters that are \nnn (n = 0-7) or \xhh (h = 0-9, a-f, A-F)

       return: -1 - false
               >=0 - the length of the char expression.
     */
    int len, i, end;

    if (arg == NULL) {
        return -1;
    }

    end = 0;
    for (i = 1, len = 1; arg[i] != '\0'; i++) {
        if (arg[i] == '\'' && arg[i-1] != '\\') {
	    len++;
	    end = 1;
	    break;
	}

        len++;
    }

    if (end == 0) {
        return -1;
    }

    if (len < 3 || len > 6 || len == 5 || arg[0] != '\'' || arg[len-1] != '\'') {
        return -1;
    }

    if (arg[1] != '\\') {
        if (len == 3 && arg[1] != '\'' && arg[1] != '\"' && arg[1] != '\?' && arg[1] != '\\') {
            return len;
	}
    } else {
        switch (len) {
	    case 4:
	        switch (arg[2]) {
		    case 'a':
		    case 'b':
		    case 'f':
		    case 'n':
		    case 'r':
		    case 't':
		    case 'v':
		    case '\\':
		    case '\'':
		    case '\?':
		    case '\"':
		        return len;
			break;
		}
		break;
	    case 6:
	        if (arg[2] >= '0' && arg[2] <= '7' && arg[3] >= '0' && arg[3] <= '7' && arg[4] >= '0' && arg[4] <= '7') {
		    return len;
		} else if (arg[2] == 'x' && ((arg[3] >= '0' && arg[3] <= '9') || (arg[3] >= 'a' && arg[3] <= 'f') || (arg[3] >= 'A' && arg[3] <= 'F')) && ((arg[4] >= '0' && arg[4] <= '9') || (arg[4] >='a' && arg[4] <= 'f') || (arg[4] >= 'A' && arg[4] <='F'))) {
		    return len;
		}
		break;
	}
    } 

    return -1;
}

/* int checkString(char line[], int from) 
   Description: verify proper string (double quotes delimited) within a line of a C program.
   Parameters: - char line[]: characters sequence that includes string(s).
               - int from: the index that the string (") starts. 
   Return: int: >= 0 the number of charactor(s) between "
                -1 something is wrong
 */
int checkString(char line[], int from) 
{
    int rv, end;

    if (from > 0 && line[from-1] != ' ' && line[from-1] != '\t' && line[from-1] != '=' && line[from-1] != ',' && line[from-1] != '(' && line[from-1] != '[' && line[from-1] != '{') {
        return -1;
    } 

    end = 0;

    for (rv = 0; line[++from] != '\0'; rv++) {
        if (line[from] == '\"' && line[from-1] != '\\' && (line[from+1] == '\n' || line[from+1] == ';' || line[from+1] == ' ' || line[from+1] == '\t' || line[from+1] == ',' || line[from+1] == ')' || line[from+1] == ']' || line[from+1] == '}')) {
	    /* end of string */
	    end = 1;
	    rv++;
	    break;
	} else {
	    if (line[from] == '\n') {
	        return -1;
	    }
	}
    }

    if (end) {
        return rv;
    } else {
        return -1;
    }
}

/*
   int checkChar(char line[], int from)
   Description: verify proper char (single quote delimited) with in a line of a C program.
   Parameters: - char line[]: characters sequence that includes string(s).
               - int from: the index that the char (') starts. 
   Return: int: >= 0 the number of charactor(s) between '
                -1 something is wrong
 */
int checkChar(char line[], int from)
{
    int rv, i, end;
    char *p;

    if (from > 0 && line[from-1] != ' ' && line[from-1] != '\t' && line[from-1] != '=' && line[from-1] != ',' && line[from-1] != '(' && line[from-1] != '[' && line[from-1] != '{') {
        return -1;
    } 

    /* The longest char expression is: '\xhh' - includes 6 characters. */
    p = malloc(7 * sizeof(char));
    
    for (i = 0; i < 6 && line[from + i] != '\0'; i++) {
        p[i] = line[from + i];
    }

    p[6] = '\0';

    rv = isValidChar(p);

    if (rv >= 0) {
        end = from + rv + 1;
        if (line[end] == ' ' || line[end] == '\t' || line[end] == '\n' || line[end] == '+' || line[end] == '-' || line[end] == '*' || line[end] == '/' || line[end] == '%' || line[end] == ',' || line[end] == ')' || line[end] == ']' || line[end] == '}') {
	    return rv;
	} else {
	    return -1;
	}
    } else {
        return -1;
    }
}

/*
    int checkComments(char line[], int from, int *ic)
    Description: Verify content of comments
    Parameters: - char line[]: characters sequence that includes comments.
                - int from: the index that the '/' starts.
		- int *ic: the address of the comments indicater.
    Return: int: >= 0 the number of charactor(s) of the comments
                 -1 something is wrong.
 */
int checkComments(char line[], int from, int *ic)
{
    int i = 0;
    if (line[from + i] == '/' && line[from + i + 1] == '*') {
        *ic = 1;
	i += 2;
    }

    while (line[from + i] != '\0') {
        if (line[from + i] == '*' && line[from + i + 1] == '/') {
	    *ic = 0;
	    i += 2;
	} else {
	    i++;
	}
    }

    return i;
}
