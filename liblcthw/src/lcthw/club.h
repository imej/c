#ifndef _club_h
#define _club_h

#include <stdio.h>
#include <stdlib.h>
#include <lcthw/hashmap.h>
#include <lcthw/bstrlib.h>
#include <assert.h>

/*definition of a member in the club */
typedef struct Person {
    char name[100];
    char address[100];
    int age;
    char hobbies[100];
} Person;

Hashmap *pdb;

void init();
void Person_print(Person *p);
#endif
