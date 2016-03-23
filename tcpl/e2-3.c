/* function htoi(s) to convert a string of hexadecimal digits 
   (including an aoptional 0x or 0X) into its equivalent integer value.
   The allowable digits are 0 ~ 9, a ~ f and A ~ F */
#include <stdio.h>
#include <limits.h>
#include <ctype.h>

int htoi(char s[]);

int main(void) 
{
    char *str1 = "0x11";
    char *str2 = "0X34";
    char *str3 = "0x2a";
    char *str4 = "0xfb";
    char *str5 = "0xwa";

    int i1, i2, i3, i4, i5;

    i1 = htoi(str1);
    i2 = htoi(str2);
    i3 = htoi(str3);
    i4 = htoi(str4);
    i5 = htoi(str5);

    if (i1 != 17) {
        printf("%s(%d) != %d", str1, i1, 17);
    }

    if (i2 != 52) {
        printf("%s(%d) != %d", str2, i2, 52);
    }
    
    if (i3 != 42) {
        printf("%s(%d) != %d", str3, i3, 42);
    }
    
    if (i4 != 251) {
        printf("%s(%d) != %d", str4, i4, 251);
    }
    
    if (i5 != -1) {
        printf("%s(%d) != %d", str5, i5, -1);
    }

    return 0;
}

/* return -1 if something is wrong, otherwise alway returns a positive int. */
int htoi(char s[])
{
    int rv = 0;
    int i = 0;
    if (s[i] == '0' && (s[i+1] == 'x' || s[i+1] == 'X')) {
        i += 2;
    }

    while (s[i] != '\0') {
        if (isdigit(s[i])) {
            rv = rv * 16 + s[i] - '0';	
	} else if (s[i] >= 'a' && s[i] <= 'f') {
	    rv = rv * 16 + s[i] - 'a' + 10;
	} else if (s[i] >= 'A' && s[i] <= 'F') {
	    rv = rv * 16 + s[i] - 'A' + 10;
	} else {
	    rv = -1;
	    break;
	}

	if (rv > UINT_MAX) {
	    rv = -1;
	    break;
	}

	i++;
    }
	
    return rv;
}
