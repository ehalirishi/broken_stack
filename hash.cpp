#include "hash.hpp"

hash_t findHash(void* buf, const size_t buf_size)
{
    hash_t hash = 5381;

    for (size_t i = 0; i < buf_size; i++) {
        hash = (hash * 31) ^ ((unsigned long long) *((char*) buf + i));
    }

    return hash;
}
