#pragma once

#include "types.h"

__attribute__((weak))
bool is_digit(char c) { return c >= '0' && c <= '9'; }
#define in_bounds(v, min, max) ((v) >= (min) && (v) <= (max))

#define DEF_FUNC(n, ret, args) ret(*n)args

