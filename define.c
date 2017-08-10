#include "define.h"


bool
isskip(char c)
{
    switch(c){
    case ' ':
    case '\t':
        return true;
        break;
    default:
        return false;
        break;
    }
}

bool
isnum(char c)
{
    return isdigit(c);
}


enum operators 
s_to_operator(const char * const s)
{
    switch(*s){
    case '+':
        return add;
        break;
    case '-':
        return sub;
        break;
    case '*':
        return mul;
        break;
    case '/':
        return div_r;
        break;
    case '(':
    case '[':
    case '{':
        return left_bracket;
        break;
    case ')':
    case ']':
    case '}':
        return right_bracket;
        break;
    default:
        ERR(err_operator_or_symbol,s);
    }
}

char *
operator_to_s(enum operators operator)
{
    switch(operator){
        case add:
            return "+";
        case sub:
            return "-";
        case mul:
            return "*";
        case div_r:
            return "/";
        case pow:
            return "^";
        case left_bracket:
            return "(";
        case right_bracket:
            return ")";
    }
}

static void
bulk_insert(struct hash_key * const table,size_t * const max_len,const char * tab[])
{
    size_t table_size = 0;
    for(int i = 0;*tab[i] != '\0';table_size++,i++)
        ;
    
    for(int i = 0;*tab[i] != '\0' && i <= table_size;i++)
        insert_hash(table,table_size,max_len,&*tab[i]);
}

struct hash_key *
symbols(size_t * const max_len,size_t * const size)
{
    struct hash_key * 
    symbols = Malloc(sizeof(struct hash_key) * (sizeof(symbol_tab) / sizeof(char *)));

    bzero(symbols,sizeof(struct hash_key) * (sizeof(symbol_tab) / sizeof(char *)));
    bulk_insert(symbols,max_len,(const char **)symbol_tab);
    *size = sizeof(symbol_tab) / sizeof(char *) - 1;
    return symbols;
}

struct hash_key *
operators(size_t * const max_len,size_t * const size)
{
    struct hash_key *
    operators = Malloc(sizeof(struct hash_key) * (sizeof(operator_tab) / sizeof(char *)));

    bzero(operators,sizeof(struct hash_key) * (sizeof(operator_tab) / sizeof(char *)));
    bulk_insert(operators,max_len,(const char **)operator_tab);
    *size = sizeof(operator_tab) / sizeof(char *) - 1;
    return operators;
}




















