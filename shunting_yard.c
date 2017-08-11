#include "shunting_yard.h"

static struct token *
op_to_token(struct operator op)
{
    static struct token token;
    
    token.type     = operator;
    token.operator = op.operator;

    return &token;
}

static struct operator *
token_to_op(struct token token)
{
    static struct operator op;

    op.operator = token.operator;
    op.count    = 1;

    return &op;
}

static struct token *
pop_all(struct stack_head * const head)
{
    static enum mode {lv1, // op.count 为 1
                      lv_more //op.count 大于 1
                     }mode = lv1;
    static struct operator op;

    if(is_empty_stack(head)){
        mode = lv1;
        bzero(&op,sizeof(struct operator));
        return NULL;
    }

    if(mode == lv1)
        op = *(struct operator *)pop(head);
    else
        op.count--;

    if(op.count == 1)
        mode = lv1;
    else
        mode = lv_more;

    return op_to_token(op);
}

static struct token *
pop_top(struct stack_head * const head)
{
    struct operator op = *(struct operator *)get_top(head);
    if(op.count == 1)
        pop(head);
    else
        ((struct operator *)get_top(head))->count--;
    return op_to_token(op);
}

static void
push_op(struct stack_head * const head,struct operator op)
{
    struct operator * top = get_top(head);
    if(top->operator == op.operator)
        top->count++;
    else
        push(head,&op);
}

static struct token *
pop_op(struct stack_head * const head,struct operator op)
{
    const struct operator * const top = get_top(head);
    struct token * tmp;

    #define comp_level(comp)  (priority(op.operator) comp priority(top->operator)) 
                                                                //比较优先级 输入比较符号 
                                                                // e.g. comp_level(<)
    if((combine(op.operator) == left  && comp_level(<=)  ) ||
       (combine(op.operator) == right && comp_level(<)   )){
           tmp = pop_top(head);
           push_op(head,op);
           return tmp;
       }
    
    push_op(head,op);
    return NULL;
    #undef comp_level
}

struct token *
shunting_yard(const struct token * const token,struct stack_head * const operators,
              struct stack_head * const bracket) 
{
    static enum mode {pop,normal} mode = normal;
    static struct stack_head * stack = NULL;
    if(stack == NULL)
        stack = operators;

    static int bracket_count = 0; //记录当前括号匹配的情况,左括号加 1,右括号减 1

    if(mode == normal){
        struct token * token = pop_all(bracket);
        if(token == NULL)
            mode = normal;
        else
            return token;
    }

    switch(token->type){
        case num:
        case symbol:
            return (struct token *)token;
        case operator:
            switch(token->operator){
                case left_bracket:
                    bracket_count++;
                    stack = bracket;
                    return NULL;
                case right_bracket:
                    bracket_count--;
                    mode = pop;
                    if(bracket_count == 0)
                        mode = normal;
                    return NULL;
                default:
                    return pop_op(stack,*token_to_op(*token));
            }
    }
}