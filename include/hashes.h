/* Murmur hash implementation: modified from - https://github.com/PeterScott */
/* FNV1A hash implementation: modified from - http://encode.ru/threads/612-Fastest-decompressor!?p=22184&viewfull=1#post22184 */

#ifndef HASHES_H
#define HASHES_H

#ifdef __GNUC__
#define FORCE_INLINE __attribute__((always_inline)) inline
#else
#define FORCE_INLINE inline
#endif

#include <stddef.h>
#include <stdint.h>

static FORCE_INLINE uint32_t rotl32(uint32_t x, int8_t r)
{
        return (x << r) | (x >> (32 - r));
}

#define	ROTL32(x,y) rotl32(x,y)
#define getblock(p, i) (p[i])

static FORCE_INLINE uint32_t fmix32(uint32_t h)
{
        h ^= h >> 16;
        h *= 0x85ebca6b;
        h ^= h >> 13;
        h *= 0xc2b2ae35;
        h ^= h >> 16;

        return h;
}

void MurmurHash3_x86_32(const void *key, int len, uint32_t seed, void *out);
uint32_t FNV1A_Hash_WHIZ(void *str, size_t wrdlen);

#endif
