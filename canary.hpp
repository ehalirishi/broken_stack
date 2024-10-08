#ifndef CANARY_HPP
#define CANARY_HPP

#include <cmath>
#define DIFFERENCE 1e-30

#define INT

#ifdef INT
    typedef int canary_t;
    #define CANARY_FORM_SPEC "%d"

    #define LEFT_CANARY  0x7AAAAAAA
    #define RIGHT_CANARY 07734
    #define CANARY_EQUAL(a, b) ((a) == (b))
#endif

#ifdef DOUBLE
    typedef double canary_t;
    #define CANARY_FORM_SPEC "%g"

    #define LEFT_CANARY  0x6A.Ep69
    #define RIGHT_CANARY 0x6969.0p0
    #define CANARY_EQUAL(a, b) (fabs(a - b) < DIFFERENCE)
#endif

#endif
