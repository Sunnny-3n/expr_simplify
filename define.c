#include "define.h"

bool
isnum(char c)
{
	return isdigit(c);
}

bool
isunknow(char c)
{
	return isalpha(c);
}

bool
issymbol(char c)
{
	switch(c)
	{
		case '+':
		case '-':
		case '*':
		case '/':
		case '^':
		case '(':
		case ')':
			return true;
		default:
			return false;
	}
}
