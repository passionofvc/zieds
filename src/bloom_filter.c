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
#include "hashes.h"

#define SET_BIT(bf, k)                                  \
        do {                                            \
                uint32_t key = (k);                     \
                bf->buf[key >> 4] |= 1 << (key & 0xf);  \
        } while(0)
#define TEST_BIT(bf, k) (bf->buf[k >> 4] & 1 << (k & 0xf))

#define H_a(pointer, bytes, out) (MurmurHash3_x86_32(pointer, bytes, 0, out))
#define H_b(pointer, bytes) (FNV1A_Hash_WHIZ(pointer, bytes))
#define G(in, scalar, pointer, bytes, size) (abs(in[0] + scalar * H_b(pointer, bytes)) % size)

void bloom_add(struct bloom_filter *bf, void *data, size_t len)
{
        uint8_t hash[4];

        H_a(data, len, hash);
        for(uint8_t i = 0; i < bf->nhashes; ++i) {
                SET_BIT(bf, G(hash, i, data, len, bf->mbits));
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
