#include "dbg.h"

/**
 * Automatic: You declare a variable on first use, and it is removed when it goes out of scrope.
 *            Without the static keyword, any variable inside a function is automatic.
 */
int automaticv()
{
    int myauto = 10;
    return myauto++;
}

/**
 * Static: Static variables exist in the same place throughout the life of the program.
 *         Variables declared outside of functions (in file scope) and inside functions
 *         with the static keyword are static.
 */
int staticv()
{
    static int myst = 10;
    return myst++;
}

int main()
{
    int i = 0;

    for (i = 0; i < 3; i++) {
	check(automaticv() == 10, "automaticv() should always return 10");
    }

    for (i = 0; i < 3; i++) {
	check(staticv() == 10+i,"static() should increase the returned value everytime.");
    }

error:
    return 0;
}
