/* Richard's assert */
#undef assert
#ifdef NDEBUG
    #define assert(A) ((void)0)
#else
    void _Assert(char *);

    #define _STR(X) _VAL(X) 
    #define _VAL(X) #X
    #define assert(A) ((A) ? (void)0 : _Assert(__FILE__ ":" _STR(__LINE__) " " #A))
#endif
