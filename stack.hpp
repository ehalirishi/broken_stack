#ifndef STACK_HPP
#define STACK_HPP

#include <cstdio>
#include "canary.hpp"
#include "hash.hpp"

enum error_t 
{
    SUCCESS,
    STK_NULL,
    DATA_NULL,
    STACK_OVERFLOW,
    CANARY_DEAD,
    HASH_CHANGED
};

#ifdef INT
    typedef int stack_el_t;
    #define STK_EL_FORM_SPEC "%d"

    #define POISON 0xEDA
#endif

#ifdef DOUBLE
    typedef double stack_el_t;
    #define STK_EL_FORM_SPEC "%g"

    #define POISON 0x15.AB0BAp228
#endif

typedef struct stk_hash_t
{
    hash_t      stack_hash;
    hash_t      data_hash;
} stk_hash_t;

typedef struct stack_t 
{
    canary_t    left_canary;
    size_t      size;
    size_t      capacity;
    stack_el_t* data_and_birds;
    stack_el_t* data; 
    canary_t    right_canary;
    stk_hash_t  hash;
} stack_t;


error_t stackCtor(stack_t* stk, size_t capacity);
error_t stackDtor(stack_t* stk);

error_t stackPush(stack_t* stk, stack_el_t value);
error_t stackPop(stack_t* stk, stack_el_t* result);

#endif
