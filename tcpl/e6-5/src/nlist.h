/* header file of nlist */
#ifndef __nlist_h__
#define __nlist_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct nlist {
    struct nlist *next;
    char *name;
    char *defn;
};

#define HASHSIZE 101

unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char *name, char *defn);
void releaselist();
void undef(char *name);

#endif
