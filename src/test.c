#include<stdio.h>
#include "../include/bloom_filter.h"

int main(void)
{
        //initialize
        struct bloom_filter *bf = bloom_init();

        //add some numbers
        bloom_insert_int(bf, 4);
        bloom_insert_int(bf, 20);
        bloom_insert_int(bf, 500);

        //prints 1 0 1
        printf("%d %d %d\n", bloom_query_int(bf, 4), 
        bloom_query_int(bf, 100),
        bloom_query_int(bf, 500)); 

        //always free
        BLOOM_FREE(bf);
}
