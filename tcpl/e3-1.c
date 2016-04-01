/* exercise 3-1. binsearch*/
#include <stdio.h>

int binsearch(int x, int v[], int n);
int newBinSearch(int x, int v[], int n);

int main(void)
{
    int v[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};
    int x;
    
    for (x = 10; x < 120; x += 5) {
        printf("------ Searching for %d ----------\n", x);
        printf("binsearch: %d\n", binsearch(x, v, 10));
        printf("newBinSearch: %d\n", newBinSearch(x, v, 10));
    }
    
    return 0;
}

int binsearch(int x, int v[], int n)
{
    int low, high, mid, i;
    
    low = 0;
    high = n - 1;
    i = 0;
    while (low <= high) {
        i++;
        mid = (low + high) / 2;
	if (x < v[mid]) {
	    high = mid - 1;
	} else if (x > v[mid]) {
	    low = mid + 1;
	} else {
	    printf("binsearch looped: %d\n", i);
	    return mid;
	}
    }

    printf("binsearch looped: %d\n", i);
    return -1;
}

int newBinSearch(int x, int v[], int n)
{
    int low, high, mid, i;
    
    low = 0;
    high = n -1;
    i = 0;
    mid = (low + high) / 2;
    while (low <= high && x != v[mid]) {
        i++;
        mid = (low + high) / 2;
	if (x <= v[mid]) {
	    high = mid - 1;
	} else {
	    low = mid + 1;
	}
    }

    if (x == v[mid]) {
        printf("newBinSearch looped: %d\n", i);
        return mid;
    }

    printf("newBinSearch: %d\n", i);
    return -1;
}
