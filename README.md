#zieds

Zieds (Latvian for flower) is a C implementation of a bloom filter.

##About

A bloom filter is a compact way to test whether an element is a member of a 
set. The filter uses m bits (16 in this implementation) per element to 
represent n elements by hashing each with k (optimal value (m / n) * ln(2)) 
different hash functions and setting the bit at every respective hash value. 
To determine if an element is present, the filter hashes the element and 
tests the bits at its hash value. If any of these bits are clear, the filter 
knows the element is not a member of the set.

##Hashing

Instead of defining k independent hash functions, this implementation 
generates them via:

g<sub>i</sub>(x) = h<sub>a</sub>(x) + i * h<sub>b</sub>(x) % number_of_bits, where i ranges from [0:k)

h<sub>a</sub>(x) - Murmur3 32-bit

h<sub>b</sub>(x) - FNV1A 32-bit

https://www.eecs.harvard.edu/~michaelm/postscripts/rsa2008.pdf

##Usage
```
//initialize
struct bloom_filter *bf = bloom_init();

//add some numbers
bloom_insert_int(bf, 4);
bloom_insert_int(bf, 20);
bloom_insert_int(bf, 500);

//prints 1 0 1
printf("%d %d %d\n", bloom_query_int(bf, 4), 
        bloom_query_int(bf, 100),
        bloom_query_int(bf, 500)); 

//always free
BLOOM_FREE(bf);
```

##Installation
```
Install to build directory:
	git clone https://github.com/grifhughes/zieds && \
	cd zieds/ && \
	mkdir build && cd build/ \
	cmake .. && make
System wide:
	git clone https://github.com/grifhughes/zieds && \
	cd zieds/ && \
	cmake . && sudo make install
```

##TODO

Add type flag to support a generic insertion/query
