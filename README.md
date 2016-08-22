#zieds
[![Build Status](https://travis-ci.org/grifhughes/zieds.svg?branch=master)](https://travis-ci.org/grifhughes/zieds)

zieds (Latvian for flower) is a lightweight library that implements a basic bloom 
filter in C. Currently supports strings/ints.

##About

A bloom filter is a compact way to test whether an element is a member of a
set. The filter uses m bits (16 in this implementation) per element to
represent n elements by hashing n<sub>i</sub> with k (optimal value (m / n) * ln(2))
different hash functions and setting the bit at every respective hash value.
To determine if an element is present, the filter hashes the desired element with the
k hash functions and tests the bit at each hash value. If any of these are clear, the
filter knows the element is not a member of the set. Insertion and querying a bloom filter are both O(k).

##Hashing

Instead of defining k independent hash functions, this implementation 
generates them via:

g<sub>i</sub>(x) = h<sub>a</sub>(x) + i * h<sub>b</sub>(x) % m, where i ranges from [0:k)

h<sub>a</sub>(x) - Murmur3 32-bit

h<sub>b</sub>(x) - FNV1A 32-bit

See src/hashes.h for implementations

https://www.eecs.harvard.edu/~michaelm/postscripts/rsa2008.pdf

##Installation
```
Build directory:
	git clone https://github.com/grifhughes/zieds && \
	cd zieds && mkdir build && cd build && \
	cmake .. && make 
System wide:
	git clone https://github.com/grifhughes/zieds && \
	cd zieds/ && cmake . && sudo make install
```

##Usage
```
#include <bloom_filter.h>

/* initialize */
struct bloom_filter *bf = bloom_init();

/* add some numbers */
bloom_insert_int(bf, 4);
bloom_insert_int(bf, 20);
bloom_insert_int(bf, 500);

/* prints 1 0 1 */
printf("%d %d %d\n", bloom_query_int(bf, 4), 
        bloom_query_int(bf, 100),
        bloom_query_int(bf, 500)); 

/* free */
BLOOM_FREE(bf);
```

##TODO

Add more functionality
