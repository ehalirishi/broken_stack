#include <cstdio>
#include <cstdlib>
#include "stack.hpp"
#include "stack_print.hpp"
#include "stack_helping_func.hpp"
#include "canary.hpp"

error_t stackCtor(stack_t* stk, size_t capacity)
{
    if (!stk)
    {
        printf( INFO_COL DEBUG_OUTPUT 
                ALERT_COL "stk address is NULL\n\n" RESET_COL,
                DEBUG_OUTPUT_INFO);
        return STK_NULL;
    }

    stk->left_canary    = LEFT_CANARY;
    stk->capacity       = capacity;
    stk->size           = 0;
    stk->right_canary   = RIGHT_CANARY;

    allocateData(stk, capacity);

    poisonStack(stk);

    findStackHash(stk, &(stk->hash));

    return SUCCESS;
}

error_t stackDtor(stack_t* stk)
{
    if (!stk)
    {
        printf( INFO_COL DEBUG_OUTPUT 
                ALERT_COL "stk address is NULL\n\n" RESET_COL,
                DEBUG_OUTPUT_INFO);
        return STK_NULL;
    }

    stk->capacity = 0;
    stk->size     = 0;

    free(stk->data_and_birds);

    return SUCCESS;
}

error_t stackPush(stack_t* stk, stack_el_t value)
{
    error_t error = SUCCESS;
    CHECK_FOR_ERRORS(stk)

    if (stk->size + 1 >= stk->capacity) 
    {
        error = expandStack(stk, stk->capacity * REALLOC_COEFF);
        if (error) {
            return error;
        }
        poisonStack(stk);
    }

    stk->data[stk->size] = value;
    stk->size++;

    findStackHash(stk, &(stk->hash));

    CHECK_FOR_ERRORS(stk);
    return SUCCESS;
}

error_t stackPop(stack_t* stk, stack_el_t* result)
{
    error_t error = SUCCESS;
    CHECK_FOR_ERRORS(stk)
    
    if (stk->size == 0) 
    {
        printf(ALERT_COL "The stack is empty, nothing to pop\n\n" RESET_COL);
        return SUCCESS;
    } // add macrostuff to tell where pop was called from    

    stk->size--;
    *result = stk->data[stk->size];
    stk->data[stk->size] = POISON;
    findStackHash(stk, &(stk->hash));

    if (stk->size <= stk->capacity / (REALLOC_COEFF * REALLOC_COEFF)) 
    {
        error = expandStack(stk, stk->capacity / REALLOC_COEFF);
        if (error) {
            return error;
        }
    }

    findStackHash(stk, &(stk->hash));
    
    CHECK_FOR_ERRORS(stk)
    return SUCCESS;
}  // TODO структура с значением + кодом ошибки.
