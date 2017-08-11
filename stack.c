#include "stack.h"
#include "next.c"

bool
is_empty_stack(const struct stack_head * const head)
{
    return head->node_count;
}

static struct stack_block *
init_stack_block(void)
{
    struct stack_block * new = Malloc(sizeof(struct stack_block));
    bzero(new,sizeof(struct stack_block));

    new->end_node = NULL;
    new->next     = NULL;
    new->prev     = NULL;
    return new;   
}

static void
add_block(struct stack_head * const head)
{
    struct stack_block * new = init_stack_block();
    head->tail->next = new;
    new->prev        = head->tail;

    head->tail       = new;
    head->block_count++;
}

static void
add_node(struct stack_block * const block,struct token token)
{
    if(block->end_node == NULL)
        block->end_node = block->block;
    else
        block->end_node++;

    *block->end_node = token;
}

static void
del_block(struct stack_head * const head)
{
        struct stack_block * tail = head->tail->prev;
        tail->next = NULL;
        free(head->tail);

        head->tail = tail;
        if(tail->end_node != NULL)
            head->node_count -= tail->end_node - tail->block;
        head->block_count--;
}

static void
del_node(struct stack_block * const block)
{
    bzero(block->end_node,sizeof(struct token));
        block->end_node--;
}

void
push(struct stack_head * const head,struct token token)
{
    if(head->block_count * BLOCK_SIZE == head->node_count)
        add_block(head);

    add_node(head->tail,token);
    head->node_count++;
}

struct token 
pop(struct stack_head * const head)
{
    struct token token = *head->tail->end_node;

    if(head->node_count == 0)
        ERR(err_pop);

    if(head->block_count * BLOCK_SIZE == head->node_count - 1)
        del_block(head);
    else
        del_node(head->tail);

    head->node_count--;
    return token;
}

struct stack_head *
init_stack_head(void)
{
    struct stack_head * head = Malloc(sizeof(struct stack_head));
    bzero(head,sizeof(struct stack_head));

    head->head = Malloc(sizeof(struct stack_block));
    head->tail = Malloc(sizeof(struct stack_block));
    bzero(head->head,sizeof(struct stack_block));
    bzero(head->tail,sizeof(struct stack_block));
    head->node_count = 0;
    head->block_count = 1;

    return head;
}