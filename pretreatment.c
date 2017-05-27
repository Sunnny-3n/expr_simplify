#include "pretreatment.h"
#include "define.h"

static int
get_size(const char s[])
{
	int output = 0;

	assert(s[0] != '\0');

	int i;
	for(i = 1;s[i] != '\0';i++)
	{
		if(s[i] == ' ')
			--output;
		else if( (s[i] == '(') && (isdigit(s[i-1]) || isunknow(s[i-1]) || (s[i-1] == ')')))
			++output;
		else if( (isunknow(s[i])) && (isdigit(s[i-1]) || isunknow(s[i-1])))
			++output;
	}
	return output + i + 1;
}

char *
pretreatment(const char s[])
{
	assert(s[0] != '0');
	char * expr = malloc(sizeof(char)*get_size(s));
	assert(expr != NULL);

	expr[get_size(s)] = '0';

	expr[0] = s[0];

	int j = 1;
	for(int i = 1;s[i] != '\0';i++)
	{
		if(s[i] == ' ')
			;
		else if( (s[i] == '(') && (isdigit(s[i-1]) || isunknow(s[i-1]) || (s[i-1] == ')')))
		{
			expr[j] = '*';
			expr[j+1] = s[i];
			j+=2;
		}
		else if( (isunknow(s[i])) && (isdigit(s[i-1]) || isunknow(s[i-1])))
		{
			expr[j] = '*';
			expr[j+1] = s[i];
			j+=2;
		}
		else
		{
			expr[j] = s[i];
			++j;
		}
	}


	return expr;
}
