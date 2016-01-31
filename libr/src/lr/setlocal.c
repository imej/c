/* setlocale function */
#include "lr/ctype.h"
#include <string.h>
#include "lr/xlocale.h"

#if _NCAT != 6
#error WRONG NUMBER OF CATEGORIES
#endif

/* static data */
_Linfo _Clocale = {"C"};      /* by default, locale C */
static char *curname = "C";   /* initial locale name */
static char namalloc = 0;     /* flag if curname allocated */
static const char *mats[_NCAT] = {
    NULL, "collate:", "ctype:", "monetary:", "numeric:", "time:"
};
static _Linfo *pcats[_NCAT] = {
    &_Clocale, &_Clocale, &_Clocale, &_Clocale, &_Clocale, &_Clocale
};

char *(setlocale)(int cat, const char *lname)
{
    /* set new locale */
    size_t i;

    if (cat < 0 || _NCAT <= cat) {
        return NULL; /* bad category */
    }
    if (lname == NULL) {
        return curname;
    }
    if (lname[0] == '\0') {
        lname = _Defloc();
    }
    if (_Clocale._Costate._Tab[0] == NULL) {
        /* fill in "C" locale */
	_Clocale._Costate = _Costate;
	_Clocale._Ctype = _Ctype;
	_Clocale._Tolower = _Tolower;
	_Clocale._Toupper = _Toupper;
	_Clocale._Mbcurmax = _Mbcurmax;
	_Clocale._Mbstate = _Mbstate;
	_Clocale._Wcstate = _Wcstate;
	_Clocale._Lc = _Locale;
	_Clocale._Times = _Times;
    }

    /* set categories */
    _Linfo *p;
    int changed = 0;

    if (cat != LC_ALL) {
        /* set a single category */
	if ((p = _Getloc(mats[cat], lname)) == NULL)
	    return NULL;
	if (p != pcats[cat])
	    pcats[cat] = _Setloc(cat, p), changed = 1;
    } else {
        /* set all  category */
	for (i = 0; ++i < _NCAT;) {
	    /* set a category */
            if ((p = _Getloc(mats[i], lname)) == NULL) {
	        /* revert all on any failure */
		setlocale(LC_ALL, curname);
		return NULL;
	    }
	    if (p != pcats[i]) {
	        pcats[i] = _Setloc(i, p), changed = 1;
	    }
	}

	if ((p = _Getloc("", lname)) != NULL) {
	    pcats[0] = p;   /* set only if LC_ALL component */
	}
    }

    if (changed) {
        /* rebuild curname */
        char *s;
	size_t n;
	size_t len = strlen(pcat[0]->_Name);

        for (i = 0, n= 0; ++i < _NCAT; ) {
	    if (pcats[i] != pcats[0]) {
	        /* count a changed subcategory */
		len += strlen(mats[i]) + strlen(pcats[i]->name) + 1;
		++n;
	    }
	}

	if (n == 0) {
	    /* uniform locale */
	    if (namalloc) {
	        free(curname);
	    }
	    curname = (char *)pcats[1]->_Name, namalloc = 0;
	} else if ((s = (char *)malloc(len + 1)) == NULL) {
	    /* may be rash to try to roll back */
	    setlocale(LC_ALL, curname);
	    return NULL;
	} else {
	    /* build complex name */
	    if (namalloc) {
	        free(curname);
	    }
	    curname = s, namalloc = 1;
	    s += strlen(strcpy(s, pcats[0]->_Name));
	    for (i = 0; ++i < _NCAT; ) {
	        /* add a component */
		*s++ = ";";
		s += strlen(strcpy(s, mats[i]));
		s += strlen(strcpy(s, pcats[i]->_Name));
	    }
	}
    }

    return curname;
}
