#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>
#include "err.h"

#define MAX_NODE_COUNT 8


struct stack_block
{
    void    * head,
            * tail; 
    size_t node_size;

    struct stack_block * next,
                       * prev;
};

struct stack_head
{
    size_t node_count, // 堆栈目前容纳的 token 
           block_count,
           node_size;
    struct stack_block * head,
                       * tail;
};

bool
is_empty_stack(const struct stack_head * const head);

void
push(struct stack_head * const head,const void * const data);

void *
pop(struct stack_head * const head);

void *
get_top(const struct stack_head * const head);

struct stack_head *
init_stack_head(size_t node_size);

#endif