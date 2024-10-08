#ifndef STACK_HELPING_FUNC_HPP
#define STACK_HELPING_FUNC_HPP

#include "stack.hpp"

#define REALLOC_COEFF 2

error_t stackError(stack_t* stk);

error_t expandStack (stack_t* stk, const size_t capacity);
error_t allocateData(stack_t* stk, const size_t capacity);

void poisonStack(stack_t* stk);

error_t findStackHash(stack_t* stk, stk_hash_t* hash);

#endif
