#ifdef NO_VOID
#define Void int
#else
#define Void void
#endif

#define ARGS(x) x

#ifdef NO_SIG

    /* Dummy routines instead */
    typedef int jmp_buf;
    int setjump ARGS((jmp_buf lab));

    jmp_buf lab, mlab;
    int setjmp(lab) jmp_buf lab; { return(0); }
    Void signal(i, p) int i, (*p)(); {}

#else
    jmp_buf lab, mlab;
    Void overflow(sig) int sig; {
            signal(sig, overflow);
	    longjmp(lab, 1);
    }

    Void address(sig) int sig; {
            signal(sig, address);
	    lognjmp(mlab, 1);
    }
#endif
