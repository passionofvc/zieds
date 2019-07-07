/*
*   Zieds - A C implementation of a bloom filter                    
*   Copyright (C) <2016>  Grif Hughes - ghughes@smu.edu
*
*   This program is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*   the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   This program is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef BLOOM_FILTER_H
#define BLOOM_FILTER_H 

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// sizeof(uint16_t) = 2bytes
//  2 << 3 = 2 * 2^3= 2*8=16
// log(2) = 0.6
// nhashes = (mbits/nelem)*ln(2)

#define BLOOM_INIT(bf, size)                                    \
    do {                                                        \
        bf = malloc(sizeof(struct bloom_filter));               \
        bf->nelems = size;                                      \
        bf->mbits = bf->nelems * (2 << 3);                      \
        bf->nhashes = 11;                                       \
        bf->buf = calloc(bf->nelems, 16);                       \
    } while(0)
#define BLOOM_FREE(bf)                                          \
    do {                                                        \
        free(bf->buf);                                          \
        free(bf);                                               \
    } while(0)

struct bloom_filter {
    uint8_t  nhashes;  /* optimal for 16 bits per element*/  /* (mbits/nelem)*ln(2)で最適化 */
    uint16_t *buf;     /* 16 bits per element */            /* 2bytes */ 
    uint32_t nelems;   /* number of elements */
    uint32_t mbits;    /* number of bits */
};

void bloom_insert_int(struct bloom_filter *bf, const int32_t data);
void bloom_insert_string(struct bloom_filter *bf, const char *data);
bool bloom_query_int(struct bloom_filter *bf, const int32_t data);
bool bloom_qury_string(struct bloom_filter *bf, const char *data);

#endif
