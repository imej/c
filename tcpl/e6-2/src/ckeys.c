/* exercise 6-2: deal with all C keywords. */
#include "header.h"

/* createKeyTree: create a tree of C keywords. */
struct tnode *createKeyTree()
{
    char *ka[] = {
        "auto",
	"break",
	"case",
	"char",
	"const",
	"continue",
	"default",
	"do",
	"double",
	"else",
	"enum",
	"extern",
	"float",
	"for",
	"goto",
	"if",
	"int",
	"long",
	"register",
	"return",
	"short",
	"signed",
	"sizeof",
	"static",
	"struct",
	"switch",
	"typedef",
	"union",
	"unsigned",
	"void",
	"volatile",
	"while"
    };
    return fromSortedArray(ka, 0, 31);
}
