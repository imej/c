#include "lr/locale.h"
#include "lr/xstate.h"
#include "lr/xtinfo.h"

typedef struct _Linfo {
    const char *_Name; /* must be first */
    struct _Linfo *_Next;

    /* controlled by LC_COLLATE */
    _Statab _Costate;

    /* controlled by LC_CTYPE */
    const short *_Ctype;
    const short *_Tolower;
    const short *_Toupper;
    unsigned char _Mbcurmax;
    _Statab _Mbstate;
    _Statab _Wcstate;

    /* controlled by LC_MONETARY and LC_NUMERIC */
    struct lconv _lc;

    /* controlled by LC_TIME */
    _Tinfo _Times;
} _Linfo;
