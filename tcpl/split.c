/* a function to split a string into an array of strings by a charactor (delimiter) 
   return: int - length of the result array.*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Token {
    char *orgStr;   /* original string needs to be split */
    char dlt;        /* delimiter */
    int ind;         /* index of the current character in the string */
} Token;

Token *Init_Token(char frm[], char dlt)
{
    int i = 0;
    int len = 0;
    while (frm[len] != '\0') {
        len++;
    }

    char *sp = malloc(len);
    for (i = 0; i < len; i++) {
        sp[i] = frm[i];
    }

    Token *p = malloc(sizeof(Token));
    p->orgStr = sp;
    p->dlt = dlt;
    p->ind = 0;

    return p;
}

void Destroy_Token(Token *t)
{
    if (t != NULL) {
        if (t->orgStr != NULL) {
	    free(t->orgStr);
	}
	free(t);
    }
}

int Has_More(Token *t)
{
    int rv = 0;
    
    if (t != NULL && t->orgStr != NULL && t->orgStr[t->ind] != '\0') {
        rv = 1;
    } 

    return rv;
}

int Get_Next(Token *t, char to[])
{
    int rv = 0;
    int quote = 0;

    if (Has_More(t)) {
        if (t->orgStr[t->ind] == '\'' || t->orgStr[t->ind] == '\"') {
	    /* quote - ignore delimiter between */
            quote = t->orgStr[t->ind];
	    t->ind++;
	}

        while (t->orgStr[t->ind] != '\0' && (quote ? (t->orgStr[t->ind] != t->dlt || t->orgStr[t->ind - 1] != quote) : (t->orgStr[t->ind] != t->dlt))) {
	    to[rv++] = t->orgStr[(t->ind)++];
	}

	if (quote) {
	    rv--;
	}

	to[rv] = '\0';
	if (t->orgStr[t->ind] == t->dlt) {
	    t->ind++;
	}
    }

    return rv;
}

void Reset_Token(Token *t)
{
    if (t != NULL) {
        t->ind = 0;
    }
}

int main(void)
{
    char *ch = "'0015014292','2016/03/03 14:46:50','ISIS','WILLIS','Seriah','Lourdes Mae','','2010/11/15 00:00:00','002','Alberta, Canada','002','007','4480331201','448','002','','Y','','013','','N','','NE6-110-19','','HIGH LEVEL','AB','T0H1Z0','7809262029','','','','','','','','','R61','135','7800000000','A','','','BARB KOMARNICKI','','','','','Heather Pollock','','','','R61','135','095A','3133','','','2012/11/08 00:00:00','013','2028/11/15 00:00:00',NULL,NULL,'',NULL,NULL,'2012/03/23 00:00:00','014','2028/11/15 00:00:00',NULL,'HARDER GETRUDA & RICHARD','','','NW 21 110 19 W5','','High Level','AB','T0H1Z0','7809262029','','7809262029','','','7808411495','','YATCHOTAY','PATRICIA','LYNN','','1981/07/22 00:00:00','001','','007','4480086302','448','','Y','','MARYANN APARTMENTS','','HIGH LEVEL','AB','T0H1Z0','7808214167','','','','7805020548','','','WILLIS','ALLEN','','','1901/01/01 00:00:00','000','','007','76200045001','762','','Y','','UNKNOWN','','MEANDER RIVER','AB','T0H1Z0','','','','','','','','SIAM_Anita.Lindstrom'";
    char tk[1000];
    int i = 0;

    Token *myt = Init_Token(ch, ',');

    while (Has_More(myt)) {
	i = Get_Next(myt, tk);
	if (i > 0) {
            printf("%s\n", tk);
	}
    }
    Destroy_Token(myt);
    return 0;
}
