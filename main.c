#include <stdio.h>
#include "define.h"
#include "stack.h"
#include "hash.h"
#include "next.h"
#include "err.h"

#define MAX 2000

static struct hash_head *
init_hash_head(void)
{
    struct hash_head * head = Malloc(sizeof(struct hash_head));
    head->symbols = symbols(&(head->max_symbol_len),&(head->symbols_len));
    head->operators = operators(&(head->max_operator_len),&(head->operators_len));
    return head;
}

static void
print_token(const struct hash_head * head,const struct token * const token)
{
    switch(token->type){
        case num:
            printf("%g ",token->num);
            return;
        case operator:
            printf("%s ",operator_to_s(token->operator));
            return;
        case symbol:
            printf("%s ",find_from_hash(head->symbols,head->symbols_len,token->symbol_hash)->name);
            return;
    }
}

int main(void)
{
    struct hash_head * head = init_hash_head();
    struct stack_head  * stack_head = init_stack_head();
    struct token * token;

    char s[MAX];
    fgets(s,MAX,stdin);

    do{ 
    token = next(s,head,stack_head);
    if(token != NULL)
        print_token(head,token);
    }while(token != NULL);
    printf("\n");
    


    return 0;
}
