/* Raise a signal with raise() */

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

int pre_fact, i;

void SIGhandler(int);

void SIGhandler(int sig)
{
    printf("\nReceived a SIGUSR1 signal! %d, %d\n", i - 1, pre_fact);
    exit(0);
}

int main()
{
    int fact;
    signal(SIGUSR1, SIGhandler);
    for (pre_fact = i = 1; ; i += 1000, pre_fact = fact) {
        fact = pre_fact * i;
	if(fact < 0) {
	    // Overflow occured
	    raise(SIGUSR1);
	} else if (i % 300 == 0) {
	    printf("    %d,    %d\n", i, fact);
	}
    }

    return 0;
}
