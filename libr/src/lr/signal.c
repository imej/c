/* signal function -- simple version */
#include "lr/signal.h"

/* external declaration */
extern _Sigfun *_Sigtable[_NSIG];

_Sigfun *(signal)(int sig, _Sigfun *fun)
{
    /* specify handler for a signal */
    _Sigfun *s;

    if (sig <= 0 || _NSIG <= sig || fun == SIG_ERR) {
        /* bad signal */
	return (SIG_ERR);
    }

    /* add machine-dependent handling here */
    s = _Sigtable[sig], _Sigtable[sig] = fun;
    return (s);
}
