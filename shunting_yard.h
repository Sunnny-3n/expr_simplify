#ifndef  SHUNTING_YARD_H_
#define SHUNTING_YARD_H_

#include "define.h"
#include "stack.h"

struct token *
shunting_yard(struct token * token,struct stack_head * head);

#endif