#ifndef NEXT_H_
#define NEXT_H_

#include <stddef.h>
#include <stdlib.h>
#include "define.h"
#include "stack.h"
#include "hash.h"


struct token *
next(const char s[],const struct hash_head * const head,
	 struct stack_head * const stack_head);

#endif