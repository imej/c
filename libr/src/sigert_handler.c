#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

static void field_abort(int sig)
{
    /* handle SIGABRT */
    puts("Continue (y/n)?\n");

    char c = getchar();

    if (c == 'y' || c == 'Y') {
        sig = SIG_IGN;
        return;
    } else {
        exit(EXIT_SUCCESS);
    }
}

int main()
{
    signal(SIGABRT, &field_abort);

    abort();

    puts("AFTER ABORT.");

    return 0;
}
