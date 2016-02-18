/* print a histogram of the lengths of the frequencies of different characters.*/
#include <stdio.h>
#include <stdlib.h>

#define BLOCK '*'

typedef struct Bar {
    char cr;
    int len;
    struct Bar *next;
} Bar;

Bar *New_Bar(char cr)
{
    Bar *rv = malloc(sizeof(Bar));
    if (rv != NULL) {
        rv->cr = cr;
        rv->len = 0;
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

    maxlen = 0;
    while ((c = getchar()) != EOF) {
	while (end != NULL && end->cr != c) {
	    end = end->next;
	}
	if (end == NULL) {
	    /* no existing, append a new one. */
	    bs = New_Bar(c);
	    if (header == NULL) { /* first one */
	        header = bs;
	    } else {
	        end = header;
	        while (end->next != NULL) {
	            end = end->next;
	        }
	        end->next = bs;
	    }
	    end = bs;
	}
        
	end->len++;
	if (end->len > maxlen) {
	    maxlen = end->len;
	}

	end = header;
     }

    end = header;

    if (argv[1][0] == 'h') {
        while (end != NULL) {
	    switch (end->cr) {
	        case '\t':
		    printf("|>:");
		    break;
		case '\n':
		    printf("|<:");
		    break;
		default:
		    printf("|%c:", end->cr);
	    }

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
	    switch (end->cr) {
	        case '\t':
		    printf(">");
		    break;
		case '\n':
		    printf("<");
		    break;
		default:
		    printf("%c", end->cr);
	    }
	    end = end->next;
	}
	printf("\n");
	end = header;
	while (end != NULL) {
	    printf("-");
	    end = end->next;
	}
	printf("\n");
    }

    Free_All(header);

    return 0;
}
