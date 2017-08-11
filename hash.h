#ifndef HASH_H_
#define HASH_H_

#include <inttypes.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include "err.h"

struct hash_key
{
    char * name;
    uint64_t hash;
    struct hash_key * next;
};

struct hash_head
{
    size_t symbols_len,operators_len;
    size_t max_symbol_len,max_operator_len;
    struct hash_key * symbols,
                      * operators;
};


uint64_t
murmur_hash64(const void * key,size_t len,int32_t seed);

uint64_t 
hash(const void * key,size_t len);

struct hash_key *
find_hash(const struct hash_key * table,size_t size,const char * const key,size_t len);

struct hash_key *
find_from_hash(const struct hash_key * table,size_t size,uint64_t hash_sum);

void
insert_hash(const struct hash_key * const table,size_t size,size_t * const max_len,const char * const key);


#endif