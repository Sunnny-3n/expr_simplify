#ifndef  SHUNTING_YARD_H_
#define SHUNTING_YARD_H_

#include "define.h"
#include "stack.h"

struct operator
{
    enum operators operator;
    int count;   /*记录该元素重复了几次 e.g.
                  *stack:++++++**^^/// 
                  *stack:+6 *2 ^2 /3          
                  */
};

struct token *
shunting_yard(const struct token * const token,struct stack_head * const operators,
              struct stack_head * const bracket);

#endif