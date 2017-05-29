#include "transform.h"

struct expr *
s_to_infix(const char s[]);

int
get_expr_size(const char s[]);

int
get_infix_size(const struct expr * const infix);

struct expr *
infix_to_RPN(const struct expr * const infix);

enum combination
combine(char c);

int
priority(char c);

int
pop_all(int i,struct expr * RPN,int top,char * stack);

int
get_stack_size(const struct expr infix[]);


struct expr *
s_to_infix(const char s[])
{
	struct expr * infix = malloc(get_expr_size(s)*sizeof(struct expr));

	static char * p_end;
	int j = 0;
	for(int i = 0;s[i] != '\0';)
	{
		if(isnum(s[i]))
		{
			infix[j].num = strtod(&s[i],&p_end);
			infix[j].type = num;
			i = (p_end - s);
			j++;
		}
		else if(isunknow(s[i]))
		{
			infix[j].unknow = s[i];
			infix[j].type = unknow;
			i++;
			j++;
		}
		else if(issymbol(s[i]))
		{
			infix[j].symbol = s[i];
			infix[j].type = symbol;
			i++;
			j++;
		}
		else
		{
			perror("错误: 输入未知符号 ");
			abort();
		}
	}
	infix[j].type = end;
	return infix;
}

struct expr *
infix_to_RPN(const struct expr * const infix)
{
	struct expr * RPN = malloc(get_infix_size(infix)*sizeof(struct expr));
	assert(RPN != NULL);

	char symbol_stack[get_stack_size(infix)],
		 bracket_stack[get_stack_size(infix)],
		 * stack = symbol_stack;

		 symbol_stack[0] = '\0';
		 bracket_stack[0] = '\0';

	int  symbol_top  = 0,
		 bracket_top = 0,
		 bracket     = 0,
		 * top		 = &symbol_top;

	int i = 0,j = 0;
	for(;infix[i].type != end;i++)
	{
		if(infix[i].type == num || infix[i].type == unknow)
		{
			RPN[j] = infix[i];
			j++;
		}
		else
		{
			switch(infix[i].symbol)
			{
				case '(':
					bracket++;
					stack = bracket_stack;
					top   = &bracket_top;
					break;
				case ')':
					bracket--;
					j = pop_all(j,RPN,*top,stack);
					if(bracket == 0)
					{
						stack = symbol_stack;
						top   = &symbol_top;
					}
					break;
				default:
					if(stack[0] == '\0')
						stack[0] = infix[i].symbol;
					else if(((combine(infix[i].symbol) == left) && (priority(infix[i].symbol) <= priority(stack[*top])))\
						 || ((combine(infix[i].symbol) == right) && (priority(infix[i].symbol) < priority(stack[*top]))))
					{
						RPN[j].type   = symbol;
						RPN[j].symbol = stack[*top];
						stack[*top]   = infix[i].symbol;
						j++;
					}
					else
					{
						stack[*top+1] = infix[i].symbol;
						(*top)++;
					}
			}
		}
	}
	j = pop_all(j,RPN,*top,symbol_stack);
	RPN[j].type = end;
	return RPN;
}

enum combination
combine(char c)
{
	switch(c)
	{
		case '+':
		case '-':
		case '*':
		case '/':
			return left;
		case '^':
			return right;
		default:
			printf("未知符号");
			abort();
	}
}

int
priority(char c)
{
	switch(c)
	{
		case '+':
		case '-':
			return 1;
		case '*':
		case '/':
			return 2;
		case '^':
			return 3;
		default:
			printf("未知符号");
			abort();
	}
}

int
pop_all(int j,struct expr * RPN,int top,char * stack)
{
	for(;top >= 0;j++,top--)
	{
		RPN[j].type = symbol;
		RPN[j].symbol = stack[top];
		stack[top] = 0;
	}
	return j;
}

int
get_expr_size(const char s[])
{
	int size = 0;
	bool flag = false; // 记录前一个字符是否是数字
	for(int i = 0;s[i] != '\0';i++)
	{
		if(isnum(s[i]))
		{
			if(flag == false)
				flag = true,size++;
			else
				; //not to do something
		}
		else if(isunknow(s[i]) || issymbol(s[i]))
			flag = false,size++;
	}

	return size;
}

int
get_stack_size(const struct expr infix[])
{
	int output = STACK_SIZE;
	for(int i = 0;infix[i].type != end;i++)
	{
		if(infix[i].type == symbol && infix[i].symbol == '^')
			output++;
	}
	return output;
}

int
get_infix_size(const struct expr * const infix)
{
	int i = 0;
	for(;infix[i].type != end;i++)
		;
	return i;
}
