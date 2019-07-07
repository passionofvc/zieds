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

#include "../include/bloom_filter.h"
#include "../include/hashes.h"
#include <stdio.h>

#define SET_BIT(bf, key)                       \
    do {                                       \
            uint32_t k = (key);                \
            bf->buf[k >> 4] |= 1 << (k % 16); \
    } while(0)

#define TEST_BIT(bf, k) (bf->buf[k >> 4] & 1 << (k % 16))
#define H_a(pointer, bytes, out) (MurmurHash3_x86_32(pointer, bytes, 0, out))
#define H_b(pointer, bytes) (FNV1A_Hash_WHIZ(pointer, bytes))
#define G(in, scalar, pointer, bytes, size) (abs(in[0] + scalar * H_b(pointer, bytes)) % size)

void bloom_add(struct bloom_filter *bf, void *data, size_t len)
{
    int8_t hash[4];

    H_a(data, len, hash);
    for(uint8_t i = 0; i < bf->nhashes; ++i) {
        uint32_t h = G(hash, i, data, len, bf->mbits); 
        printf("h=[%d], h>>4=[%d], (h%16)=[%d], 1<< (h%16)=[%d]\n", h, h>>4, h%16, 1<< (h%16) );
        SET_BIT(bf, h);
    }
}

bool bloom_test(const struct bloom_filter *bf, void *data, size_t len)
{
    uint8_t hash[4];

    H_a(data, len, hash);
    for(uint8_t i = 0; i < bf->nhashes; ++i) {
        uint32_t key = G(hash, i, data, len, bf->mbits);
        if(!TEST_BIT(bf, key)) {
            return false;
        }
    }
    return true;
}

void bloom_insert_int(struct bloom_filter *bf, const int32_t data) {
    const int32_t * pData = &data;
    const uint64_t len = sizeof(data);
    bloom_add(bf, (void*)pData, len);
}

void bloom_insert_string(struct bloom_filter *bf, const char *data) {
    const uint64_t len = strlen(data);
    bloom_add(bf, (void*)data, len);
}


bool bloom_query_int(struct bloom_filter *bf, const int32_t data) {
    const int32_t * pData = &data;
    const size_t len = sizeof(data);
    return bloom_test(bf, (void*)pData, len);
}

bool bloom_qury_string(struct bloom_filter *bf, const char *data) {
    const size_t len = strlen(data);
    return bloom_test(bf, (void*)data, len);
}
