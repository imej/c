/* print a histogram of the lengths of words in its input.*/
#include <stdio.h>
#include <stdlib.h>

#define BLOCK '*'

typedef struct Bar {
    int len;
    struct Bar *next;
} Bar;

Bar *New_Bar(int l)
{
    Bar *rv = malloc(sizeof(Bar));
    if (rv != NULL) {
        rv->len = l;
	rv->next = NULL;
    }

    return rv;
}

void Free_All(Bar *all)
{
    Bar *current = all;

    while (current != NULL) {
        all = all->next;
	free(current);
	current = all;
    }
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: please indicate the direction of the histogram: h - horizontal, v - vertical.\n");
	return 1;
    }

    Bar *header = NULL;
    Bar *end = NULL;
    Bar *bs;
    int c, i, maxlen;

    i = 0;
    maxlen = 0;
    while ((c = getchar()) != EOF) {
        if (c != ' ' && c != '\n' && c != '\t') {
	    i++;
	} else if (i > 0) {
	    bs = New_Bar(i);
	    if (end != NULL) {
	        end->next = bs;
		end = bs;
	    } else {
	        header = end = bs;
	    }

	    if (i > maxlen) {
	        maxlen = i;
	    }

	    i = 0;
	}
    }

    end = header;

    if (argv[1][0] == 'h') {
        while (end != NULL) {
            printf("|");
            for (i = 0; i < end->len; i++) {
	        printf("%c", BLOCK);
	    }
	    printf("\n");
            end = end->next;
        }
    } else {
        printf("\n\n\n");
	for (i = maxlen; i > 0; i--) {
	    while (end != NULL) {
	        if (end->len >= i) {
		    printf("%c", BLOCK);
		} else {
		    printf(" ");
		}

		end = end->next;
	    }
            printf("\n");
	    end = header;
	}

	end = header;
	while (end != NULL) {
	    printf("_");
	    end = end->next;
	}
	printf("\n");
    }

    Free_All(header);

    return 0;
}
