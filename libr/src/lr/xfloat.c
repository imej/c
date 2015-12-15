/* values used by <float.h> macros -- IEEE 754 version */
#include <float.h>

/* macros */
#define DFRAC   (49+_DOFF)
#define DMAXE   ((1U<<(15-_DOFF))-1)
#define FFRAC   (17+_FOFF)
#define FMAXE   ((1U<<(15-_FOFF))-1)
#define LFRAC   (49+_LOFF)
#define LMAXE   0x7fff    
#define LOG2    0.30103   
#if _D0 != 0      /* low to high words */
#define DINIT(w0, wx) wx, wx, wx, w0
#define FINIT(w0, wx) wx, w0
#define LINIT(w0, w1, wx) wx, wx, wx, w1, w0
#else              /* high to low words */
#define DINIT(w0, wx) w0, wx, wx, wx
#define FINIT(w0, wx) w0, wx
#define LINIT(w0, w1, wx) w0, w1, wx, wx, wx
#endif

/* static data */
_Dvals _Dbl = {
    (int)((DFRAC-1)*LOG2),                   /* DBL_DIG */
    (int)DFRAC,                         /* DBL_MANT_DIG */
    (int)((DMAXE-_DBIAS-1)*LOG2),     /* DBL_MAX_10_EXP */
    (int)(DMAXE-_DBIAS-1),               /* DBL_MAX_EXP */
    (int)(-_DBIAS*LOG2),              /* DBL_MIN_10_EXP */
    (int)(1-_DBIAS),                     /* DBL_MIN_EXP */
    {DINIT(_DBIAS-DFRAC+2<<_DOFF, 0)},   /* DBL_EPSILON */
    {DINIT((DMAXE<<_DOFF)-1, -0)},           /* DBL_MAX */
    {DINIT(1<<_DOFF, 0)},                    /* DBL_MIN */
};


