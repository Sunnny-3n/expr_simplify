#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include "define.h"

#ifndef TRANSFORM_H_
#define TRANSFORM_H_

#define MAX 50

/*
*优先级为从左到右的符号有 + - * /
*因为桟中 top 符号的优先级必须比加入的符号的优先级大,否则将被弹出(两者都为从左到右)
*
*所以桟中最多储存两个优先级为从左到右的符号
*所以 桟 大小为 2
 */

#define STACK_SIZE 2

enum datatype {num,unknow,symbol,end};
enum combination {left,right};

struct expr
{
	enum datatype type;
	union
	{
		double num;
		char unknow;
		char symbol;
	};
}expr;

struct expr *
s_to_infix(const char s[]);

struct expr *
infix_to_RPN(const struct expr[]);

#endif
