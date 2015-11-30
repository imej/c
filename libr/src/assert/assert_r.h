/**
 * Richard's assert-h
 */
#undef assert_r
#ifdef NDEBUG
    #define assert_r(A) ((void)0)
#else
    void _Assert_r(char *);

    #define _STR(X) _VAL(X) 
    #define _VAL(X) #X
    #define assert_r(A) ((A) ? (void)0 : _Assert_r(__FILE__ ":" _STR(__LINE__) " " #A))
#endif
