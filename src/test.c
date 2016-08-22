#include<stdio.h>
#include "../include/bloom_filter.h"

int main(void)
{
        //initialize
        struct bloom_filter *bf = bloom_init();

        //add some strings 
        bloom_insert_string(bf, "Hello");
        bloom_insert_string(bf, "Hey");
        bloom_insert_string(bf, "Sup");

        //prints 0 0 1
        printf("%d %d %d\n", bloom_query_string(bf, "Hi"), 
        bloom_query_string(bf, "Yo"),
        bloom_query_string(bf, "Hey")); 

        //always free
        BLOOM_FREE(bf);
}
