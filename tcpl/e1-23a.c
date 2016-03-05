/* remove all comments of a c file. */
#include <stdio.h>

int main(int argc, char* argv[]) 
{
    char *filename;

    if (argc != 2) {
        printf("USAGE: ./a.out filename\n");
	return 1;
    }

    filename = argv[1];
    printf("Filename: %s\n", filename);

    return 0;
}
