/* exercise 4-2: atof handles scientific notation 123.45e-6 */
#include <ctype.h>
#include <stdio.h>

#define MAXLINE 100

int catchline(char [], int);
double atof(char []);

int main(void)
{
    double sum;
    char line[MAXLINE];

    sum = 0;
    while (catchline(line, MAXLINE) > 0) {
        printf("\t%g\n", sum += atof(line));
    }
    return 0;
}

double atof(char s[])
{
    double val, power, rv;
    int i, sign, ne, ex;

    for (i = 0; isspace(s[i]); i++)
        ;
    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-') {
        i++;
    }
    for (val = 0.0; isdigit(s[i]); i++) {
        val = 10.0 * val + (s[i] - '0');
    }

    power = 1.0;
    if (s[i] == '.') {
        i++;
        for (; isdigit(s[i]); i++) {
            val = 10.0 * val + (s[i] - '0');
	    power *= 10.0;
        }
    }

    rv = sign * val / power;

    if (s[i] == 'e' || s[i] == 'E') {
        i++;
	if (s[i] == '-') {
	    ne = -1;
	    i++;
	} else {
	    ne = 1;
	}
        for (ex = 0; isdigit(s[i]); i++) {
	    ex = 10 * ex + (s[i] - '0');
	}

        while (ex > 0) {
	    rv = (ne == -1) ? rv / 10.0 : rv * 10.0;
	    ex--;
	}

    }

    return rv;
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
