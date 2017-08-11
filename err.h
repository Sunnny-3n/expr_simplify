#ifndef ERR_H_
#define ERR_H_

#include <stdlib.h>
#include <stdarg.h> 
#include <stdio.h>
//#include <varargs.h>
#include <unistd.h>
#include "define.h"
 

enum err_msg{not_enough_mem,err_operator_or_symbol,
             err_operator,err_bracket,err_combine,
             err_priority,err_pop};

void
print_err_msg(enum err_msg msg,...);

void *
Malloc(size_t size);

#define ERR(...){                                                                                 \
                    print_err_msg(__VA_ARGS__);                                                   \
                    fprintf(stderr,"\nfile:%s func:%s line:%d \n",__FILE__,__FUNCTION__,__LINE__);\
                    exit(1);                                                                      \
                }                                                                                 \

#endif