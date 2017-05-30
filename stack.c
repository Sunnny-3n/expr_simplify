#include "stack.h"

struct polynomial *
add_item(const struct expr RPN,struct polynomial * const top);

void
assign_fraction(struct monomial * const monomial,double numerator,double denominator);

void
assign_unknow(struct monomial * const monomial,char c);

struct polynomial *
initialize(void);

void
add_num(double num,struct polynomial * new);

void
add_unknow(char unknow,struct polynomial * new);

void
add_at_end(struct polynomial * new,struct polynomial * const top);




struct polynomial *
add_item(const struct expr  RPN,struct polynomial * const top)
{
	struct polynomial * new = initialize();

	if(top == NULL)
	{
		switch(RPN.type)
		{
			case num:
				add_num(RPN.num,new);
				return new;
			case unknow:
				add_unknow(RPN.symbol,new);
				return new;
			default:
			abort();
		}
	}
	else
	{
		switch(RPN.type)
		{
			case num:
				add_num(RPN.num,new);
				add_at_end(new,top);
				return new;
			case unknow:
				add_unknow(RPN.symbol,new);
				add_at_end(new,top);
				return new;
			default:
			abort();
		}
	}
}

void
assign_fraction(struct monomial * const monomial,double numerator,double denominator)
{
	(*monomial).numerator = numerator;
	(*monomial).denominator = denominator;
}

void
assign_unknow(struct monomial * const monomial,char c)
{
	if(c == '\0')
	{
		(*monomial).alpha = malloc(sizeof(struct unknow));
		assert(((*monomial).alpha) != NULL);
		//结尾
		(*monomial).alpha[0].unknow = '\0';
		(*monomial).alpha[0].power  = 0;
	}
	else
	{
		(*monomial).alpha = malloc(sizeof(struct unknow)*2);
		assert(((*monomial).alpha) != NULL);

		(*monomial).alpha[0].unknow = c;
		(*monomial).alpha[0].power  = 1;
		//结尾
		(*monomial).alpha[1].unknow = '\0';
		(*monomial).alpha[1].power  = 0;
	}

}

struct polynomial *
initialize(void)
{
	struct polynomial
	* new = malloc(sizeof(struct polynomial));
	assert(new != NULL);

	(*new).numerator.next = NULL;
	(*new).denominator.next = NULL;
	(*new).prev = NULL;
	(*new).next = NULL;

	return new;
}

void
add_num(double num,struct polynomial * new)
{
	//分子
	assign_fraction(&((*new).numerator),num,1);
	assign_unknow(&((*new).numerator),'\0');

	//分母
	assign_fraction(&((*new).denominator),1,1);
	assign_unknow(&((*new).denominator),'\0');
}

void
add_unknow(char unknow,struct polynomial * new)
{
	//分子
	assign_fraction(&((*new).numerator),1,1);
	assign_unknow(&((*new).numerator),unknow);

	//分母
	assign_fraction(&((*new).denominator),1,1);
	assign_unknow(&((*new).denominator),'\0');
}

void
add_at_end(struct polynomial * new,struct polynomial * const top)
{
	(*new).next = NULL;
	(*new).prev = top;
	(*top).next = new;
}
