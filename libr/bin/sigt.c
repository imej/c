#include <stdio.h>
typedef void (*_Sigfun)(int);

#define SIG_DFL (_Sigfun *)0
#define SIG_ERR (_Sigfun *)-1
#define SIG_IGN (_Sigfun *)1

int main()
{
    _Sigfun sigtable[3] = {1};
    int inttable[3] = {1};
    int i = 0;
    for (i = 0; i < 3; i++) {
        if (sigtable[i] == SIG_DFL) {
	    printf ("sigtable[%d] = SIG_DFL\n", i);
	} else {
	    printf ("sigtable[%d] != SIG_DFL\n", i);
	}
	printf("inttable[%d] = %d\n", i, inttable[i]);
    }
}
