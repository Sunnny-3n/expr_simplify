#ifndef DEFINE_H_
#define DEFINE_H_

#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include "hash.h"
#include "err.h"

#define is_left_bracket(token)  (token.type == operator && token.operator == left_bracket)
#define is_right_bracket(token) (token.type == operator && token.operator == right_bracket)
#define is_symbol(token)        (token.type == symbol)
#define is_num(token)     (token.type == num)

enum operators {add,sub,mul,div_r/*div 与 stdlib.h 中的 div 重名*/,
                pow,left_bracket,right_bracket};

static char * symbol_tab[]   = {"a","b","c","d","x","y","z","\0"};
static char * operator_tab[] = {"+","-","*","/","(",")","[","]","{","}","\0"};


struct token
{
    enum type{operator,num,symbol} type;
    union
    {
        enum operators operator;
        double num;
        uint64_t symbol_hash; 
    };
};

bool
isskip(char c);

bool
isnum(char c);

enum operators 
s_to_operator(const char * const s);

char *
operator_to_s(enum operators operator);

struct hash_key *
operators(size_t * const max_len,size_t * const size);

struct hash_key *
symbols(size_t * const max_len,size_t * const size);

#endif