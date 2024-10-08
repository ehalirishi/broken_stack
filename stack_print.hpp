#ifndef STACK_PRINT_HPP
#define STACK_PRINT_HPP

#include "stack.hpp"

#define DEBUG_OUTPUT "<%s> %s() line %d:\n\t"
#define DEBUG_OUTPUT_INFO __FILE__, __func__, __LINE__

#define CHECK_FOR_ERRORS(stk)   error = STACK_ASSERT(stk);\
                                if (error) { \
                                    return error; \
                                }

#define RESET_COL   "\033[0m"               // sets console color to normal
#define ALERT_COL   "\033[1;31m"            // red
#define NAME_COL    "\033[1;34m"            // blue
#define INFO_COL    "\033[1;32m"            // green
#define POISON_COL  "\033[01;07;38;05;190m" // neon yellow background
#define DATA_COL    "\033[38;05;214m"       // orange
#define CANARY_COL  "\033[38;05;226m"       // yellow
#define HASH_COL    "\033[38;05;82m"        // neon green

void stackDump( const stack_t* stk,
                error_t occured_error, const char file_name[], 
                const char func_name[], const int line_num,
                const char stk_name[]);
void printData(const stack_t* stk);

error_t stackAssert(stack_t* stk, const char file_name[],
                    const char func_name[], const int line_num, 
                    const char stk_name[]);

#define STACK_DUMP(stk, occured_error) stackDump(stk, occured_error, __FILE__, __func__, __LINE__, #stk);
#define STACK_ASSERT(stk) stackAssert(stk, __FILE__, __func__, __LINE__, #stk);

#endif
