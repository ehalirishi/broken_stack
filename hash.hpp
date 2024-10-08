#ifndef HASH_HPP
#define HASH_HPP

#include <cstdio>

typedef unsigned long long hash_t;

hash_t findHash(void* buf, const size_t buf_size);

#endif
