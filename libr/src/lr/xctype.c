/* _Ctype conversion table -- ASCII versin */
#include "lr/ctype.h"
#include <limits.h>  // UCHAR_MAX
#include <stdio.h>   // EOF

#if EOF != -1 || UCHAR_MAX != 255
    #error WRONG CTYPE TABLE
#endif

/* macros */
#define XDI (_DI | _XD)    // hex
#define XLO (_LO | _XD)
#define XUP (_UP | _XD)

/* static data */
static const short ctyp_tab[257] = {0, /*EOF*/
    _BB, _BB, _BB, _BB, _BB, _BB, _BB, _BB,
    _BB, _CN, _CN, _CN, _CN, _CN, _BB, _BB,
    _BB, _BB, _BB, _BB, _BB, _BB, _BB, _BB,
    _BB, _BB, _BB, _BB, _BB, _BB, _BB, _BB,
    _SP, _PU, _PU, _PU, _PU, _PU, _PU, _PU,
    _SP, _PU, _PU, _PU, _PU, _PU, _PU, _PU,
    XDI, XDI, XDI, XDI, XDI, XDI, XDI, XDI,
    XDI, XDI, _PU, _PU, _PU, _PU, _PU, _PU,
    _PU, XUP, XUP, XUP, XUP, XUP, XUP, _UP,
    _UP, _UP, _UP, _UP, _UP, _UP, _UP, _UP,
    _UP, _UP, _UP, _UP, _UP, _UP, _UP, _UP,
    _UP, _UP, _UP, _PU, _PU, _PU, _PU, _PU,
    _PU, XLO, XLO, XLO, XLO, XLO, XLO, _LO,
    _LO, _LO, _LO, _LO, _LO, _LO, _LO, _LO,
    _LO, _LO, _LO, _LO, _LO, _LO, _LO, _LO,
    _LO, _LO, _LO, _PU, _PU, _PU, _PU, _BB,
};

const short *_Ctype = &ctyp_tab[1];
