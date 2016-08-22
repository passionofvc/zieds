project(zieds)
add_executable(zieds 
	include/bloom_filter.h 
	src/hashes.h
	src/bloom_filter.c
	src/test.c)
