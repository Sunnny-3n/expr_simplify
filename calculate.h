#include "transform.h"

struct unknow
{
	char unknow;
	int power;
};

struct monomial
{
	struct coefficient
	{
		double numerator;
		double denominator;
	}coefficient;

	struct unknow * alpha;

	struct monomial * next;
}monomial;

struct algebraic_expr
{
	struct polynomial
	{
		struct monomial * numerator,
						* denominator;
	}polynomial;

	struct algebraic_expr * prev,
					  	  * next;
};

struct algebraic_expr *
calculate(struct expr RPN[]);
