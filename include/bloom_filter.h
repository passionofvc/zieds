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
#define SET_BIT(bf, k) ((bf->buf[k >> 4]) |= (1 << (k % 16)))
#define TEST_BIT(bf, k) ((bf->buf[k >> 4]) & (1 << (k % 16)))

#define ALLOC_ERR 43 
#define ALLOC_FILTER(bf) (bf = malloc(sizeof(struct bloom_filter)))
#define ALLOC_FILTER_BUF(bf_buf, nelems) (bf_buf = calloc(nelems, sizeof(uint16_t)))
#define BLOOM_FREE(bf) \
        do { \
                free(bf->buf); \
                free(bf); \
        } while(0)

struct bloom_filter {
        uint8_t nhashes; //optimal number of hashes, unless explicit (m / n * ln(2))
        uint16_t *buf; //16 bits per element 
        uint32_t nelems; //number of elements 
        uint32_t mbits; //number of bits (16 * nelems)
};

//Inits
struct bloom_filter *bloom_init();
struct bloom_filter *bloom_init_nelems(uint32_t nelems);
struct bloom_filter *bloom_init_nhashes(uint32_t nelems, uint8_t nhashes);

//Functions
void bloom_insert_int(struct bloom_filter *bf, const int32_t data);
void bloom_insert_string(struct bloom_filter *bf, const char *data);
bool bloom_query_int(struct bloom_filter *bf, const int32_t data);
bool bloom_query_string(struct bloom_filter *bf, const char *data);

#endif