#ifndef _YVALS_H
#define _YVALS_H

#define _EDOM   33
#define _ERANGE 34
#define _EFPOS  35
#define _ERRMAX 36
#define _D0     3 
#define _DBIAS  0x3fe
#define _DLONG  1 
#define _DOFF   4 
#define _FBIAS  0x7e
#define _FOFF   7 
#define _FRND   1 
#define _LBIAS  0x3ffe
#define _LOFF   15

/* for signal.h */
#define _SIGABRT 6
#define _SIGMAX  32

/* for limits.h */
#define _ILONG 1  /* nonzero if an int has 4 bytes. */
#define _CSIGN 1 /* nonzero if a char is singed */
#define _C2 1 /* 1 if the encoding is two's complement, else 0 */
#define _MBMAX 16 /* the worst-case length of a single multibyte charactet. */

/* for locale.h */
#define _NULL (void *)0
#endif
