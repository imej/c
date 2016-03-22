/* determine the ranges of char, short, int and long, 
   both singed and usigned, by printing appropriate values
   from standard headers (limits.h) and by direct compution. */
#include <stdio.h>
#include <limits.h>

char minSchr();
char maxSchr();
unsigned char maxUchr();
short minSsht();
short maxSsht();
unsigned short maxUsht();
int minSint();
int maxSint();
unsigned int maxUint();
long minSlng();
long maxSlng();
unsigned long maxUlng();

int main(void)
{
    /* print from stand header */
    printf("From limits.h:\n");

    printf("signed char is from %d to %d\n", SCHAR_MIN, SCHAR_MAX);
    printf("unsigned char is from %d to %d\n", 0, UCHAR_MAX);

    printf("signed short is from %d to %d\n", SHRT_MIN, SHRT_MAX);
    printf("unsigned short is from %d to %d\n", 0, USHRT_MAX);

    printf("signed int is from %d to %d\n", INT_MIN, INT_MAX);
    printf("unsigned int is from %d to %u\n", 0, UINT_MAX);

    printf("signed long is from %ld to %ld\n", LONG_MIN, LONG_MAX);
    printf("unsigned long is from %d to %lu\n", 0, ULONG_MAX);

    /* print by direct compution */
    printf("From direct compution:\n");

    printf("signed char is from %d to %d\n", minSchr(), maxSchr());
    printf("unsigned char is from %d to %u\n", 0, maxUchr());

    printf("signed short is from %d to %d\n",minSsht(), maxSsht());
    printf("unsigned short is from %d to %d\n", 0, maxUsht());

    printf("signed int is from %d to %d\n", minSint(), maxSint());
    printf("unsigned int is from %d to %u\n", 0, maxUint());

    printf("signed long is from %ld to %ld\n", minSlng(), maxSlng());
    printf("unsigned long is from %d to %lu\n", 0, maxUlng());



    return 0;
}

char minSchr()
{
    char rv = 1;
    int i = sizeof(char);
    return (rv << (i * 8 - 1));
}

char maxSchr()
{
    char rv = 1;
    int i = sizeof(char);
    return (rv << (i * 8 - 1)) - 1; 
}

unsigned char maxUchr()
{
    char rv = 0;
    return ~rv;
}

short minSsht()
{
    short rv = 1;
    int i = sizeof(short);
    return (rv << (i * 8 - 1));
}

short maxSsht()
{
    short rv = 1;
    int i = sizeof(short);
    return (rv << (i * 8 - 1)) - 1; 
}

unsigned short maxUsht()
{
    short rv = 0;
    return ~rv;
}

int minSint()
{
    int rv = 1;
    int i = sizeof(int);
    return (rv << (i * 8 - 1));
}

int maxSint()
{
    int rv = 1;
    int i = sizeof(int);
    return (rv << (i * 8 - 1)) - 1; 
}

unsigned int maxUint()
{
    int rv = 0;
    return ~rv;
}

long minSlng()
{
    long rv = 1;
    int i = sizeof(long);
    return (rv << (i * 8 - 1));
}

long maxSlng()
{
    long rv = 1;
    int i = sizeof(long);
    return (rv << (i * 8 - 1)) - 1; 
}

unsigned long maxUlng()
{
    long rv = 0;
    return ~rv;
}
