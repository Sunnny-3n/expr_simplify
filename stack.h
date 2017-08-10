#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>
#include "define.h"
#include "err.h"

#define BLOCK_SIZE 8


struct stack_block
{
    struct token   block[BLOCK_SIZE],
                 * end_node; 

    struct stack_block * next,
                       * prev;
};

struct stack_head
{
    size_t node_count, // 堆栈目前容纳的 token 
           block_count;
    struct stack_block * head,
                       * tail;
};

bool
is_empty_stack(const struct stack_head * const head);

void
push(struct stack_head * const head,struct token token);

struct token 
pop(struct stack_head * const head);

struct stack_head *
init_stack_head(void);

#endif