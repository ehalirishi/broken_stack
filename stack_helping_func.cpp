#include <cstdlib>
#include <cstring>
#include "stack.hpp"
#include "stack_print.hpp"
#include "stack_helping_func.hpp"
#include "hash.hpp"

error_t stackError(stack_t* stk)
{  
    if (!stk) {
        return STK_NULL;
    }

    if (!CANARY_EQUAL(stk->left_canary, LEFT_CANARY) || !CANARY_EQUAL(stk->right_canary, RIGHT_CANARY)) {
        return CANARY_DEAD;
    }

    if (stk->capacity < stk->size) {
        return STACK_OVERFLOW;
    }

    if (!stk->data_and_birds || !stk->data) {
        return DATA_NULL;
    }

    stk_hash_t temp_hash = {};
    findStackHash(stk, &temp_hash);

    if (temp_hash.stack_hash != stk->hash.stack_hash) {
        return HASH_CHANGED;
    }

    return SUCCESS;
}

error_t expandStack(stack_t* stk, const size_t capacity)
{
    error_t error;
    CHECK_FOR_ERRORS(stk) // ! локальные переменные

    stk->capacity = capacity;
    stk->data_and_birds = (stack_el_t*) realloc(stk->data_and_birds, (capacity + 2) * sizeof(stack_el_t));
    if (!stk->data_and_birds) 
    {
        printf( INFO_COL DEBUG_OUTPUT 
                ALERT_COL "couldn't reallocate memory for data\n" RESET_COL, 
                DEBUG_OUTPUT_INFO);
        return DATA_NULL;
    }

    stk->data_and_birds[capacity + 1] = RIGHT_CANARY;

    stk->data = stk->data_and_birds + 1;

    return SUCCESS;
}

error_t allocateData(stack_t* stk, const size_t capacity)
{
    if (!stk)
    {
        printf( INFO_COL DEBUG_OUTPUT 
                ALERT_COL "stk address is NULL\n\n" RESET_COL,
                DEBUG_OUTPUT_INFO);
        return STK_NULL;
    }

    stk->data_and_birds = (stack_el_t*) calloc(capacity + 2, sizeof(stack_el_t));
    if (!stk->data_and_birds) 
    {
        printf( INFO_COL DEBUG_OUTPUT 
                ALERT_COL "couldn't allocate memory for data\n\n" RESET_COL, 
                DEBUG_OUTPUT_INFO);
        return DATA_NULL;
    }
    
    stk->data_and_birds[0] = LEFT_CANARY;
    stk->data_and_birds[capacity + 1] = RIGHT_CANARY;
    
    stk->data = stk->data_and_birds + 1;

    return SUCCESS;
}

void poisonStack(stack_t* stk)
{
    for (size_t i = stk->size; i < stk->capacity; i++) {
        stk->data[i] = POISON;
    }
}

error_t findStackHash(stack_t* stk, stk_hash_t* hash)
{
    if (!stk)
    {
        printf( INFO_COL DEBUG_OUTPUT 
                ALERT_COL "stk address is NULL\n\n" RESET_COL,
                DEBUG_OUTPUT_INFO);
        return STK_NULL;
    }

    hash->stack_hash = findHash(stk, sizeof(stack_t) - 16);
    hash->data_hash  = findHash(stk->data_and_birds, stk->capacity + 2);

    return SUCCESS;
}
