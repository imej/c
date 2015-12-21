/* Test -D option of gcc
 * 1) When compile this program with: gcc filename.c -o filename
 *     It prints "MY_DEF:0" 
 *     which means macro MY_DEF is not defined.
 * 2) When compile this program with: gcc -DMY_DEF filename.c -o filename
 *     It prints "MY_DEF:1"
 *     which means macro MY_DEF is defined.
 */
#include <stdio.h>

#ifdef MY_DEF
    #define MY_DEF 1
#else
    #define MY_DEF 0
#endif

int main()
{
    printf("MY_DEF:%d\n", MY_DEF);
}
