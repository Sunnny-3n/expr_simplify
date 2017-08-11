#include "err.h"


void
print_err_msg(enum err_msg msg,...)
{
    va_list args;  
    va_start(args,msg);

    fprintf(stderr,"ERR: ");

    switch(msg){
    case not_enough_mem:
        fprintf(stderr,"没有足够的内存 ");
        break;
    case err_operator_or_symbol:
        fprintf(stderr,"未定义的运算符或未知数 %s ",va_arg(args,char *));
        break;
    case err_bracket:
        fprintf(stderr,"括号匹配不全 ");
        break;
    case err_combine:
        fprintf(stderr,"未定义运算符 %s 的结合性 ",operator_to_s(va_arg(args,int)));
        break;
    case err_priority:
        fprintf(stderr,"未定义运算符 %s 的优先级 ",operator_to_s(va_arg(args,int)));
        break;
    case err_operator:
        fprintf(stderr,"%s 运算符使用不当 ",va_arg(args,char *));
        break;
    case err_pop:
        fprintf(stderr,"pop 操作元素个数不能为 0");
        break;
    }
    va_end(args);
}

void *
Malloc(size_t size)
{
    void * new = malloc(size);
    if(new == NULL)
        ERR(not_enough_mem);
    bzero(new,size);
    return new;
}