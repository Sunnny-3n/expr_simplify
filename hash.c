#include "hash.h"

uint64_t
murmur_hash64(const void * key,size_t len,int32_t seed )
{
     const uint32_t m = 0x5bd1e995;
     const int32_t r = 24;
     uint32_t h1 = seed ^ len;
     uint32_t h2 = 0;

     const uint32_t * data = (const uint32_t *)key;

     while(len >= 8){
         uint32_t k1 = *data++;
         k1 *= m; k1 ^= k1 >> r; k1 *= m;
         h1 *= m; h1 ^= k1;
         len -= 4;

         uint32_t k2 = *data++;
         k2 *= m; k2 ^= k2 >> r; k2 *= m;
         h2 *= m; h2 ^= k2;
         len -= 4;
     }

     if(len >= 4){
         uint32_t k1 = *data++;
         k1 *= m; k1 ^= k1 >> r; k1 *= m;
         h1 *= m; h1 ^= k1;
         len -= 4;
     }

     switch(len){
         case 3: h2 ^= ((unsigned char*)data)[2] << 16;
         case 2: h2 ^= ((unsigned char*)data)[1] << 8;
         case 1: h2 ^= ((unsigned char*)data)[0];
         h2 *= m;
     };

      h1 ^= h2 >> 18; h1 *= m;
      h2 ^= h1 >> 22; h2 *= m;
      h1 ^= h2 >> 17; h1 *= m;
      h2 ^= h1 >> 19; h2 *= m;

      uint64_t h = h1;
      h = (h << 32) | h2; 
      return h;
 }

uint64_t 
hash(const void * key,size_t len)
{
    int32_t seed = 1257785213;
    return murmur_hash64(key,len,seed);
}

static bool
is_empty(const struct hash_key * key)
{
    struct hash_key empty;
    bzero(&empty,sizeof(struct hash_key));

    return !(memcmp(key,&empty,sizeof(struct hash_key)));
}


static struct hash_key *
search(const struct hash_key * table,size_t size,uint64_t hash_sum)
{
    table = &table[hash_sum % size];

    while(table->hash != hash_sum && table->next != NULL)
        table = table->next;
    return (struct hash_key *)table;
}

struct hash_key *
find_hash(const struct hash_key * table,size_t size,const char * const key,size_t len)
{
    uint64_t hash_sum = hash(key,len);
    table = search(table,size,hash_sum);

    if(table->hash != hash_sum)
        return NULL;

    return (struct hash_key *)table;
}

struct hash_key *
find_from_hash(const struct hash_key * table,size_t size,uint64_t hash_sum)
{
    table = search(table,size,hash_sum);

    if(table->hash != hash_sum)
        return NULL;

    return (struct hash_key *)table;
}

void
insert_hash(const struct hash_key * const table,size_t size,size_t * const max_len,const char * const key)
{
    uint64_t hash_sum = hash(key,strlen(key) * sizeof(char));
    struct hash_key * hash_key = search(table,size,hash_sum);

    if(strlen(key) > *max_len)
        *max_len = strlen(key);
        
    if(hash_key->hash != hash_sum){
        if(is_empty(hash_key) == false){
            hash_key->next = Malloc(sizeof(struct hash_key));
            hash_key       = hash_key->next;
        }else
            hash_key->next = NULL;

        hash_key->hash = hash_sum;

        char * s = Malloc((strlen(key) + 1) * sizeof(char));
        memmove(s,key,(strlen(key) + 1) * sizeof(char));
        hash_key->name = s; 
    }
}