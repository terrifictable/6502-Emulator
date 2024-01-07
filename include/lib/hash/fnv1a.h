#pragma once

#include "types.h"
#include "str.h"

#define FNV1A32_OFFSET 0x811c9dc5
#define FNV1A32_PRIME  0x01000193

// #define FNV_64_OFFSET 0x811c9dc5
// #define FNV_64_PRIME  0x01000193 

#define fnv1a_c(chr, hash, prime) (((hash) ^ (chr)) * prime)

__attribute__((weak, always_inline))
i32 fnv1a32(str_t* str) {
    i32 hash  = FNV1A32_OFFSET;
    str_t cpy = nstr(str->str);
    while (cpy.len--) {
        hash = fnv1a_c(*str->str++, hash, FNV1A32_PRIME);
    } 
    return hash;
}

