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
#include <stdlib.h>
#include <stdbool.h>

//Helper macros
#define SET_BIT(bf, k) ((bf->buf[k >> 5]) |= (1 << (k % 32)))
#define TEST_BIT(bf, k) ((bf->buf[k >> 5]) & (1 << (k % 32)))

#define ALLOC_ERR 43 
#define ALLOC_FILTER (malloc(sizeof(struct bloom_filter)))
#define ALLOC_FILTER_BUF(nelems) (calloc(nelems, sizeof(uint32_t)))
#define BLOOM_FREE(bf) \
        do { \
                free(bf->buf); \
                free(bf); \
        } while(0)

struct bloom_filter {
        uint32_t *buf; //32 bits per element 
        uint32_t nelems; //number of elements 
        uint32_t mbits; //number of bits (32 * nelems)
        uint32_t nh; //optimal number of hashes, unless explicit ((mbits/nelems) * ln(2))
};

//Inits
struct bloom_filter *bloom_init();
struct bloom_filter *bloom_init_cap(uint32_t cap);
struct bloom_filter *bloom_init_nhashes(uint32_t cap, uint32_t nhashes);

//Functions
void bloom_insert_int(struct bloom_filter *bf, const int32_t data);
void bloom_insert_string(struct bloom_filter *bf, const char *data);
bool bloom_query_int(struct bloom_filter *bf, const int32_t data);
bool bloom_query_string(struct bloom_filter *bf, const char *data);

#endif
