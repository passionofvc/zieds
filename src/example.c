#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../include/bloom_filter.h"
#include "../include/hashes.h"

void test_bloom_filter_string();
//void test_bloom_filter_int();

int main(int args, char * argv[])
{
    //test_bloom_filter_string();
    //size_t s = sizeof(uint16_t) << 3;
    //size_t s = sizeof(uint16_t) ;
    //printf("%zu\n", s);
    //printf("%lf\n", log(2));

    //const int32_t key = 10000;
    //int len = sizeof(key);
    //uint32_t seed = 10;
    //uint32_t hash_out[1];

    //printf("size=%d\n",  sizeof(hash_out) / sizeof(hash_out[0]) );
    //MurmurHash3_x86_32(&key, len, seed, hash_out);
    //for(size_t i=0; i< sizeof(hash_out)/sizeof(hash_out[0]); i++) {
    //    printf("%u\n", hash_out[i]);
    //}
    
    //uint32_t r= FNV1A_Hash_WHIZ((void *)&key, len);
    //printf("r=%u\n", r);

    //uint32_t k = 1200;
    //uint32_t k2 = k >> 4;
    //uint32_t k3 = 1 << (k % 16);
    //uint32_t k4 =0;
    //k4 = ( k4 |= k3 );
    //uint32_t k5 = ( k4 & k3 );
    
    
    //printf("k2=%u\n", k2);
    //printf("k3=%u\n", k3);
    //printf("k4=%u\n", k4);
    //printf("k5=%u\n", k5);
    struct bloom_filter *bf = NULL;
    BLOOM_INIT(bf, 1);

    bloom_insert_int(bf, 1);
    int r = bloom_query_int(bf, 1);
    printf("%d\n", r);

    BLOOM_FREE(bf);

    return 0;
}

void test_bloom_filter_string(){
    /* initialize */
    struct bloom_filter *bf;
    BLOOM_INIT(bf, 500);

    /* add words to filter */
    char *data[] = { "one", "three", "five", "seven", "nine", "ten"};
    size_t len_data = sizeof(data) / sizeof(data[0]);
    for(size_t i = 0; i < len_data; ++i) {
        bloom_add(bf, (void *)data[i], strlen(data[i]));
    }

    /* test set of words */
    char *test[] = { "zero", "two", "four", "six", "eight", "ten"};
    size_t len_test = sizeof(test) / sizeof(test[0]);
    for(size_t i = 0; i < len_test; ++i) {
        printf("%d\t", bloom_test(bf, (void *)test[i], strlen(test[i])));
    }
    printf("%s", "\n");

    /* free */
    BLOOM_FREE(bf);
}

