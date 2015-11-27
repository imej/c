/* ispunct function */
#include "ctype_r.h"

int (ispunct)(int c)
{
    return (_Ctype[c] & _PU);
}
