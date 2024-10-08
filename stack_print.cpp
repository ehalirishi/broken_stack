#include <cstdio>
#include "stack.hpp"
#include "stack_print.hpp"
#include "stack_helping_func.hpp"

void stackDump( const stack_t* stk,
                error_t occured_error, const char file_name[], 
                const char func_name[], const int line_num,   // !  разбить на функции
                const char stk_name[])
{
    printf( ALERT_COL   "Stack" 
            NAME_COL    " %s" 
            ALERT_COL   " dumped in"
            INFO_COL    " <%s> %s() line %d:\n" RESET_COL, 
            stk_name, file_name, func_name, line_num);
    
    printf("         Stack address: " DATA_COL "[%p]\n" RESET_COL, stk);
    if (occured_error == STK_NULL) 
    {
        printf(ALERT_COL "stack address is NULL, you can't dump stack\n\n" RESET_COL);
        return;
    }
    
    printf("       stk_left_canary: " CANARY_COL CANARY_FORM_SPEC "\n" RESET_COL,  stk->left_canary);
    printf("      stk_right_canary: " CANARY_COL CANARY_FORM_SPEC "\n" RESET_COL, stk->right_canary);
    if (!CANARY_EQUAL(stk->left_canary, LEFT_CANARY)) 
    {
        printf(ALERT_COL "left stack canary has died\n\n" RESET_COL);
        return;
    }
    if (!CANARY_EQUAL(stk->right_canary, RIGHT_CANARY)) 
    {
        printf(ALERT_COL "right stack canary has died\n\n" RESET_COL);
        return;
    } 

    printf("        Stack capacity: " DATA_COL "%zu\n" RESET_COL, stk->capacity);
    printf("            Stack size: " DATA_COL "%zu\n" RESET_COL, stk->size    );
    if (stk->capacity < stk->size) 
    {
        printf(ALERT_COL "stack overflow\n\n" RESET_COL);
        return;
    }

    printf("data_and_birds address: " DATA_COL "[%p]\n" RESET_COL, stk->data_and_birds);
    if (!stk->data_and_birds)
    {
        printf(ALERT_COL "data_and_birds address is NULL, you can't read data\n\n" RESET_COL);
        return;
    }

    printf("          data address: " DATA_COL "[%p]\n" RESET_COL, stk->data);
    if (!stk->data)
    {
        printf(ALERT_COL "stack data address is NULL, you can't read data\n\n" RESET_COL);
        return;
    }

    printf("      data_left_canary: " CANARY_COL CANARY_FORM_SPEC "\n" RESET_COL,  stk->data_and_birds[0]);
    printf("     data_right_canary: " CANARY_COL CANARY_FORM_SPEC "\n" RESET_COL, stk->data_and_birds[stk->capacity + 1]);
    if (!CANARY_EQUAL(stk->data_and_birds[0], LEFT_CANARY)) 
    {
        printf(ALERT_COL "left data canary has died\n\n" RESET_COL);
        return;
    }
    if (!CANARY_EQUAL(stk->data_and_birds[stk->capacity + 1], RIGHT_CANARY)) 
    {
        printf(ALERT_COL "right data canary has died\n\n" RESET_COL);
        return;
    }

    printf("            Stack hash: " HASH_COL "%llx\n" RESET_COL, stk->hash.stack_hash);
    if (occured_error == HASH_CHANGED)
    {
        printf(ALERT_COL "hash is wrong\n\n" RESET_COL);
        return;
    }
    
    printf("             data hash: " HASH_COL "%llx\n" RESET_COL, stk->hash.data_hash);
    if (occured_error == HASH_CHANGED)
    {
        printf(ALERT_COL "hash is wrong\n\n" RESET_COL);
        return;
    }

    printData(stk);
}

void printData(const stack_t* stk)
{
    printf("{\n");

    for (size_t i = 0; i < stk->size; i++) {
        printf( INFO_COL "\t*[%03zu] " 
                DATA_COL STK_EL_FORM_SPEC "\n" RESET_COL, 
                i, stk->data[i]);
    }     

    for (size_t i = stk->size; i < stk->capacity; i++) {
        printf( INFO_COL "\t [%03zu] " 
                POISON_COL STK_EL_FORM_SPEC " (POISON)\n" RESET_COL, 
                i, stk->data[i]);
    }   

    printf("}\n");
}

error_t stackAssert(stack_t* stk, const char file_name[],
                    const char func_name[], const int line_num, 
                    const char stk_name[])
{
    error_t error = stackError(stk);
    if (error)
    {
        printf( ALERT_COL   "Stack" 
                NAME_COL    " %s" 
                ALERT_COL   " asserted in"
                INFO_COL    " <%s> %s() line %d:\n" RESET_COL, 
                stk_name, file_name, func_name, line_num);
        stackDump(stk, error, file_name, func_name, line_num, stk_name);
    }
    return error;
}
