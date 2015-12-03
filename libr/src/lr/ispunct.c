/* ispunct function */
#include "lr/ctype.h"

int (ispunct)(int c)
{
    return (_Ctype[c] & _PU);
}
