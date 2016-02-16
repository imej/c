/* verify that the expression getchar() != EOF is 0 or 1 */
#include <stdio.h>

main()
{
    /* On Redhat, to enter EOF, enter ^d (ctrl+d)*/
    printf("getchar() != EOF == %d", getchar() != EOF);
}
