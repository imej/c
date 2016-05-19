/* this test does not use the minunit.h. */
#include <header.h>
#include <stdio.h>
#include <string.h>


int main(void)
{
    char grp[MAXLINE] = {0};
    struct tnode *tree = read();

    prtgrp(tree, 6, grp);
    tdestroy(tree);

    return 0;
}
