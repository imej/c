/* ctype.h standard header */
#ifndef _CTYPE
#define _CTYPE

/* _Ctype code bits */
#define _XA 0x200 /* extra alphabetic       */
#define _XS 0x100 /* extra spacei           */
#define _BB 0x80  /* BEL, BS, etc.          */
#define _CN 0x40  /* CR, FF, HT, NL, VT     */
#define _DI 0x20  /* '0'-'9'                */
#define _LO 0x10  /* 'a'-'z'                */
#define _PU 0x08  /* punctuation            */
#define _SP 0x04  /* space                  */
#define _UP 0x02  /* 'A'-'Z'                */
#define _XD 0x01  /* '0'-'9', 'a'-'z', 'A'-'Z' */

/* declarations */
int ispunct(int c);
extern const short *_Ctype, *_Tolower, *_Toupper;

/* ctype_chk argument */
#define ctype_chk(A) (A)<0 || (A)>256 ? -1 : (A)

/* macro overrides */
#define isalnum(c) (_Ctype[ctype_chk((int)(c))] & (_DI|_LO|_UP|_XA))
#define isalpha(c) (_Ctype[ctype_chk((int)(c))] & (_LO|_UP|_XA))
#define iscntrl(c) (_Ctype[ctype_chk((int)(c))] & (_BB|_CN))
#define isdigit(c) (_Ctype[ctype_chk((int)(c))] & _DI)
#define isgraph(c) (_Ctype[ctype_chk((int)(c))] & (_DI|_LO|_PU|_UP|_XA))
#define islower(c) (_Ctype[ctype_chk((int)(c))] & _LO)
#define isprint(c) (_Ctype[ctype_chk((int)(c))] & (_DI|_LO|_PU|_SP|_UP|_XA))
#define ispunct(c) (_Ctype[ctype_chk((int)(c))] & _PU)
#define isspace(c) (_Ctype[ctype_chk((int)(c))] & (_CN|_SP|_XS))
#define isxdigit(c) (_Ctype[ctype_chk((int)(c))] & _XD)
#define isupper(c) (_Ctype[ctype_chk((int)(c))] & _UP)
#define tolower(c) _Tolower[ctype_chk((int)(c))]
#define toupper(c) _Toupper[ctype_chk((int)(c))]

#endif
