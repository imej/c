/* this test does not use the minunit.h. */
#include <header.h>
#include <stdio.h>
#include <string.h>


int main(int argc, char *argv[])
{
    int num = 6;
    char grp[MAXLINE] = {0};
    struct tnode *tree = read();

    if (argc > 1) {
        num = atoi(argv[1]);
    }
    prtgrp(tree, num, grp);
    tdestroy(tree);

    return 0;
}
