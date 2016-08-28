#zieds

zieds (Latvian for flower) is a lightweight library that implements a basic bloom 
filter in C. Currently supports strings/ints.

##About

A bloom filter is a compact way to test whether an element is a member of a set. The 
filter uses m bits (16 in this implementation) per element to represent n elements by 
hashing n<sub>i</sub> with k (optimal value (m / n) * ln(2)) different hash functions 
and 
setting the bit at every respective hash value. To determine if an element is 
present, the filter hashes the desired element with the k hash functions and tests 
the bit at each hash value. If any of these are clear, the filter knows the element 
is not a member of the set. Insertion and querying a bloom filter are both O(k).

##Hashing

Instead of defining k independent hash functions, this implementation generates them 
via:

g<sub>i</sub>(x) = h<sub>a</sub>(x) + i * h<sub>b</sub>(x) % m, where i ranges from 
[0:k)

h<sub>a</sub>(x) - Murmur3 32-bit

h<sub>b</sub>(x) - FNV1A 32-bit

See src/hashes.h for implementations

https://www.eecs.harvard.edu/~michaelm/postscripts/rsa2008.pdf

##Installation
```
git clone https://github.com/grifhughes/zieds && \
cd zieds && mkdir build && cd build && \
cmake .. && make
```

##Usage
```
/* initialize */
struct bloom_filter *bf;
BLOOM_INIT(bf);

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

/* prints 0 0 0 0 0 1 */
```

##TODO

Add more functionality
