#include <cstdio>
#include "stack.hpp"
#include "stack_print.hpp"
#define CHECK if (!error) error =

// Пуш и поп лучше использовать вместе с CHECK, чтобы в случае ошибки они не выполнялись
// Внизу пример работающего кода
// Одна ошибка вроде простая, но её легко промограть
// Вторая идейно несложная, но очень душная как по мне
// Версия на самом деле очень сырая и тут много вещей, которые можно было бы поменять, но имеем, что имеем :'[

int main(void)
{
    error_t error = SUCCESS;
     
    stack_t stk = {};
    error = stackCtor(&stk, 15);

    for (size_t i = 0; i < 15; i++)
    {
        CHECK stackPush(&stk, (stack_el_t) i);
        STACK_DUMP(&stk, error);
    }

    stack_el_t x;

    for (size_t i = 0; i < 15; i++) {
        CHECK stackPop(&stk, &x);
        STACK_DUMP(&stk, error);
    }
    
    STACK_DUMP(&stk, error);

    stackDtor(&stk);  
    
    return error;
}
