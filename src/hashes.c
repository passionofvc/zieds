#include "../include/hashes.h"

void MurmurHash3_x86_32(const void *key, int len, uint32_t seed, void *out)
{
        int i;
        uint32_t h1 = seed;
        uint32_t c1 = 0xcc9e2d51;
        uint32_t c2 = 0x1b873593;
        const int nblocks = len / 4;
        const uint8_t *data = (const uint8_t *)key;
        const uint32_t *blocks = (const uint32_t *)(data + nblocks*4);

        for(i = -nblocks; i; i++) {
                uint32_t k1 = getblock(blocks,i);
                k1 *= c1;
                k1 = ROTL32(k1,15);
                k1 *= c2;
                h1 ^= k1;
                h1 = ROTL32(h1,13); 
                h1 = h1 * 5 + 0xe6546b64;
        }

        uint32_t k1 = 0;
        const uint8_t *tail = (const uint8_t *)(data + nblocks*4);

        switch(len & 3) {
                case 3: k1 ^= tail[2] << 16;
                case 2: k1 ^= tail[1] << 8;
                case 1: k1 ^= tail[0];
                k1 *= c1; k1 = ROTL32(k1,15); k1 *= c2; h1 ^= k1;
        };

        h1 ^= len;
        h1 = fmix32(h1);
        *(uint32_t *)out = h1;
}

uint32_t FNV1A_Hash_WHIZ(void *str, size_t wrdlen)
{
        char *p = (char *)str;
        uint32_t hash32 = 2166136261;
        const uint32_t prime = 1607;
                     
        for(; wrdlen >= sizeof(uint32_t); wrdlen -= sizeof(uint32_t), p += sizeof(uint32_t)) {
                hash32 = (hash32 ^ *(uint32_t *)p) * prime;
        }
        if (wrdlen & sizeof(uint16_t)) {
                hash32 = (hash32 ^ *(uint16_t *)p) * prime;
                p += sizeof(uint16_t);
        }
        if (wrdlen & 1) hash32 = (hash32 ^ *p) * prime;
                                 
        return hash32 ^ (hash32 >> 16);
}
