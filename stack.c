#include "stack.h"

bool
is_empty_stack(const struct stack_head * const head)
{
    return !(head->node_count);
}

static struct stack_block *
init_block(size_t node_size)
{
    struct stack_block * new = Malloc(sizeof(struct stack_block));

    new->node_size = node_size;
    new->head     = Malloc(node_size * MAX_NODE_COUNT);
    new->tail     = NULL;
    new->next     = NULL;
    new->prev     = NULL;
    return new;   
}

static void
add_block(struct stack_head * const head,size_t node_size)
{
    struct stack_block * new = init_block(node_size);
    head->tail->next = new;
    new->prev        = head->tail;

    head->tail       = new;
    head->block_count++;
}

static void
add_node(struct stack_block * const block,const void * const data)
{
    if(block->tail == NULL)
        block->tail = block->head;
    else
        block->tail += block->node_size;

    block->tail = memmove(block->tail,data,block->node_size);
}

static void
del_block(struct stack_head * const head)
{
    struct stack_block * tail = head->tail;
    if(tail->head == tail->tail)
        head->node_count--;
    else
        head->node_count -= (tail->tail - tail->head) / tail->node_size;

    tail = head->tail->prev;
    tail->next = NULL;
    free(head->tail);

    head->tail = tail;
    head->block_count--;
}

static void
del_node(struct stack_block * const block)
{
    bzero(block->tail,block->node_size);
    block->tail -= block->node_size;
}

void
push(struct stack_head * const head,const void * const data)
{
    if(head->block_count * MAX_NODE_COUNT == head->node_count)
        add_block(head,head->node_size);

    add_node(head->tail,data);
    head->node_count++;
}

void *
get_top(const struct stack_head * const head)
{
    return head->tail->tail;
}

void *
pop(struct stack_head * const head)
{
    void * data = Malloc(head->node_size);
    data = memmove(data,get_top(head),head->node_size);

    if(is_empty_stack(head))
        return NULL;

    if(head->block_count * MAX_NODE_COUNT == head->node_count - 1)
        del_block(head);
    else
        del_node(head->tail);

    head->node_count--;
    return data;
}

struct stack_head *
init_stack_head(size_t node_size)
{
    struct stack_head * head = Malloc(sizeof(struct stack_head));

    head->head = init_block(node_size);
    head->tail = head->head;
    head->node_size = node_size;
    head->node_count = 0;
    head->block_count = 1;

    return head;
}