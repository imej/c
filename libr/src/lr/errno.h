#ifndef _ERRNO_H
#define _ERRNO_H
#ifndef _YVALS_H
    #include "lr/yvals.h"
#endif

/* error codes */
#define EDOM   _EDOM
#define ERANGE _ERANGE
#define EFPOS  _EFPOS

/* add yours here */
#define _NERR _ERRMAX

/* declarations */
extern int errno_r;
#endif
