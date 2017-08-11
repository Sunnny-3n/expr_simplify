#ifndef  SHUNTING_YARD_H_
#define SHUNTING_YARD_H_

#include "define.h"
#include "stack.h"

struct token *
shunting_yard(struct token *(* next)(const char s[],const struct hash_head * const head,
                                     struct stack_head * const stack_head));

#endif