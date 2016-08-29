#include <stdio.h>
#include <string.h>
#include "../include/bloom_filter.h"

int main(void)
{
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

        /* free */
        BLOOM_FREE(bf);
}
