#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>
#include <assert.h>
#include "transform.h"

struct unknow
{
	char unknow;
	int power;
};

struct monomial
{
//		coefficient
		double numerator,
			   denominator;

	struct unknow * alpha;
	struct monomial * next;


};

struct polynomial
{
	struct monomial numerator,
					denominator;

	struct polynomial * prev,
					  * next;
};

struct polynomial *
add_item(struct expr  RPN,struct polynomial * const top);



















#endif
