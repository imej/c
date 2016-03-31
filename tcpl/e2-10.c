/* exercise 2-10 function lower with a conditional expression */
#include <stdio.h>

char lower(char ch);

int main(void)
{
    char str[20] = "abcjkluyni123ABCDE89";
    int i;

    printf("%s\n", str);
    for(i = 0; i < 20; i++) {
        str[i] = lower(str[i]);
    }

    printf("%s\n", str);
    return 0;
}

char lower(char ch)
{
    return ((ch >= 'a' && ch <= 'z' ? ch - 'a' + 'A' : ch));
}
