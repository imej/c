/* this test does not use the minunit.h. */
#include <header.h>
#include <stdio.h>
#include <string.h>


int main(void)
{
    struct tnode *tree = read();
    treeprint(tree);
    tdestroy(tree);

    return 0;
}
