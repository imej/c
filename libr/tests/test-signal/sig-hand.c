#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void INThandler(int);

int main()
{
    /*
     * Function signal() returns 
     * 1) a pointer to the  previous handler. Or
     * 2) SIG_ERR
     *
     * signal(SIGINT, SIG_IGN) != SIG_IGN means that signal SIGINT was not
     * ignored until this statement.It should be ignored since this statement, 
     * unless it fails and returns SIG_ERR 
     */
    // signal(SIGINT, SIG_IGN);
    if (signal(SIGINT, SIG_IGN) != SIG_IGN) {
        printf("Installing INThandler.\n");
        signal(SIGINT, INThandler);

        while(1) {
            pause();
        }
    } else {
        printf("SIGINT has been igored already.\n");
    }

    return 0;
}

void INThandler(int sig)
{
    char c;
    signal(sig, SIG_IGN);

    printf("Ouch, did you hit Ctrl-C?\nDo you want to quit [y/n]?");

    c = getchar();
    if (c == 'y' || c == 'Y') {
        exit(0);
    } else {
        signal(SIGINT, INThandler);
    }
}
