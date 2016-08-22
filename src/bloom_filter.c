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

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "../include/bloom_filter.h"
#include "hashes.h"

//Helper macros
#define SET_BIT(bf, k) (bf->buf[k >> 4] |= 1 << (k % 16))
#define TEST_BIT(bf, k) (bf->buf[k >> 4] & 1 << (k % 16))

#define ALLOC_ERR 43 
#define ALLOC_FILTER(bf) (bf = malloc(sizeof(struct bloom_filter)))
#define ALLOC_FILTER_BUF(bf_buf, nelems) (bf_buf = calloc(nelems, sizeof(uint16_t)))

//Generic hash wrappers
#define H_a(pointer, bytes, out) (MurmurHash3_x86_32((void *)pointer, bytes, 0, out))
#define H_b(pointer, bytes) (FNV1A_Hash_WHIZ((void *)pointer, bytes))
#define G(in, scalar, pointer, bytes, size) (abs(in[0] + scalar * H_b(pointer, bytes)) % size)

struct bloom_filter *bloom_init() 
{
        struct bloom_filter *bf;

        ALLOC_FILTER(bf);
        if(bf == NULL) {
                perror("Alloc failed, exiting...");
                exit(ALLOC_ERR);
        }

        bf->nelems = 100;
        bf->mbits = bf->nelems * (sizeof(uint16_t) << 3);
        bf->nhashes = (bf->mbits / bf->nelems) * log(2); 

        ALLOC_FILTER_BUF(bf->buf, bf->nelems);
        if(bf->buf == NULL) {
                free(bf);
                perror("Alloc failed, exiting...");
                exit(ALLOC_ERR);
        }

        return bf;
}

struct bloom_filter *bloom_init_nelems(uint32_t nelems)
{
        struct bloom_filter *bf;

        ALLOC_FILTER(bf);
        if(bf == NULL) {
                perror("Alloc failed, exiting...");
                exit(ALLOC_ERR);
        }

        bf->nelems = nelems;
        bf->mbits = bf->nelems * (sizeof(uint16_t) << 3);
        bf->nhashes = (bf->mbits / bf->nelems) * log(2); 

        ALLOC_FILTER_BUF(bf->buf, bf->nelems);
        if(bf->buf == NULL) {
                free(bf);
                perror("Alloc failed, exiting...");
                exit(ALLOC_ERR);
        }

        return bf;
}

struct bloom_filter *bloom_init_nhashes(uint32_t nelems, uint8_t nhashes) 
{
        struct bloom_filter *bf;

        ALLOC_FILTER(bf);
        if(bf == NULL) {
                perror("Alloc failed, exiting...");
                exit(ALLOC_ERR);
        }

        bf->nelems = nelems;
        bf->mbits = bf->nelems * (sizeof(uint16_t) << 3);
        bf->nhashes = nhashes; 

        ALLOC_FILTER_BUF(bf->buf, bf->nelems);
        if(bf->buf == NULL) {
                free(bf);
                perror("Alloc failed, exiting...");
                exit(ALLOC_ERR);
        }

        return bf;
}

void bloom_insert_int(struct bloom_filter *bf, const int32_t data)
{
        uint32_t hash[4];
        
        H_a(&data, sizeof(data), hash);
        uint8_t i;
        for(i = 0; i < bf->nhashes; ++i) 
                SET_BIT(bf, G(hash, i, &data, sizeof(data), bf->mbits));
}

void bloom_insert_string(struct bloom_filter *bf, const char *data)
{
        uint32_t hash[4];
        uint64_t len = strlen(data);
        
        H_a(&data, len, hash);
        uint8_t i;
        for(i = 0; i < bf->nhashes; ++i)
                SET_BIT(bf, G(hash, i, data, len, bf->mbits));
}

bool bloom_query_int(struct bloom_filter *bf, const int32_t data)
{
        uint32_t hash[4];

        H_a(&data, sizeof(data), hash);
        uint8_t i;
        for(i = 0; i < bf->nhashes; ++i) 
                if(!TEST_BIT(bf, G(hash, i, &data, sizeof(data), bf->mbits)))
                        return false;
        return true;
}

bool bloom_query_string(struct bloom_filter *bf, const char *data)
{
        uint32_t hash[4];
        uint64_t len = strlen(data);

        H_a(&data, sizeof(data), hash);
        uint8_t i;
        for(i = 0; i < bf->nhashes; ++i) 
                if(!TEST_BIT(bf, G(hash, i, data, len, bf->mbits)))
                        return false;
        return true;
}
