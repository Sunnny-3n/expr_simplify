#include "next.h"

static struct hash_key *
max_match(const struct hash_key * table, size_t size,
		  size_t max_len, const char * const key) 
{
	struct hash_key * hash_key = NULL;
	for(int i = 1; i <= max_len; i++)
		if(find_hash(table, size, key, i * sizeof(char)) != NULL)
			hash_key = find_hash(table, size, key, i * sizeof(char));

	return hash_key;
}

static int 
set_num(struct token * const token, const char * const s) 
{
	char * end = (char *)s;
	token->type = num;
	token->num = strtod(s, &end);

	if (end == NULL)
		return 0;
	else
		return end - s;
}

static bool 
isoperator(const struct hash_head * const head,const char * const key) 
{
	return max_match(head->operators, head->operators_len, head->max_operator_len,
					 key);
}

static int 
set_operator(struct token * const token, const char * const s,
			 const struct hash_head * const head) 
{
	struct hash_key * hash_key = max_match(head->operators, head->operators_len,
										   head->max_operator_len, s);
	token->type = operator;
	token->operator= s_to_operator(hash_key->name);
	return strlen(hash_key->name);
}

static bool 
issymbol(const struct hash_head *const head,
					 const char *const key) 
{
	return max_match(head->symbols, head->symbols_len, head->max_symbol_len, key);
}

static int 
set_symbol(struct token * const token, const char * const s,
		   const struct hash_head * const head) 
{
	struct hash_key * hash_key =
		max_match(head->symbols, head->symbols_len, head->max_symbol_len, s);

	token->type = symbol;
	token->symbol_hash = hash_key->hash;
	return strlen(hash_key->name);
}

/*按照规则添加 mul e.g.
* x(x+y)     =  x*(x+y)
* xy         =  x*y
* 3x         =  3*x
* (x+1)(x-1) =  (x+1)*(x-1)
*/
static bool
rule_add_mul(struct stack_head * head, struct token before,struct token now) 
{
	// x(x+y) = x*(x+y)
	if(is_symbol(before)       && is_left_bracket(now))   goto add_mul;
		// xy = x*y
	if(is_symbol(before)       && is_symbol(now))         goto add_mul;
	// 3x = 3*x
	if(is_num(before)          && is_symbol(now))         goto add_mul;
	//(x+1)(x-1) =  (x+1)*(x-1)
	if(is_right_bracket(before) && is_left_bracket(now))  goto add_mul;

	return false;

	add_mul:{
		struct token fill;
		fill.type     = operator;
		fill.operator = mul;
		push(head,now);
		push(head,fill);
		return true;
	}
}

struct token *
next(const char s[],const struct hash_head * const head,
	 struct stack_head * const stack_head) 
{
	static int src = 0;
	static struct token before,now;

	pop_all:
	for(int i = stack_head->node_count;i > 0;i--){  
		static struct token tmp;   
		tmp = pop(stack_head);     
		return &tmp;               
	}

	#define SETS(func){                                       \
		before = now;                                         \
		src   += func;                                        \
		if(rule_add_mul(stack_head,before,now) == true)       \
			goto pop_all;									  \
		else                                                  \
			return &now;                                      \
	}                                                         \

	if(s[src] == '\0' || s[src] == '\n')
		return NULL;
	while(isskip(s[src]))
		src++;

	if(isnum(s[src]))
		SETS(set_num(&now,&s[src]))
	if(isoperator(head, &s[src]))
		SETS(set_operator(&now, &s[src], head))
	if(issymbol(head, &s[src]))
		SETS(set_symbol(&now, &s[src], head))

	
	ERR(err_operator_or_symbol, &s[src]);
	return NULL;
	#undef SETS
}