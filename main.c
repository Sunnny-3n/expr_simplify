#include "pretreatment.h"
#include "transform.h"
#include <stdio.h>

void print_infix(struct expr * p)
{
	for(int i = 0;p[i].type != end;i++)
	{
		if(p[i].type == num)
			printf("%*.0lf",p[i].num);
		if(p[i].type == unknow)
			printf("%c",p[i].unknow);
		if(p[i].type == symbol)
			printf("%c",p[i].symbol);
		printf(" ");
	}
	printf("\n");
}

int
main(void)
{
	char s[] = "(x+1)/(x-1)*(x-1)";
	char * p = pretreatment(s);
	printf("%s\n",p);

	struct expr * ptr = s_to_infix(p);
	print_infix(ptr);

	struct expr * ptr2 = infix_to_RPN(ptr);
	print_infix(ptr2);

	return 0;
}
