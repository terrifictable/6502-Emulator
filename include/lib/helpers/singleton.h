#pragma once


#define MAKE_SINGLETON(T, n, init) \
    inline T _singleton_##n = init; \
    inline T *n = &_singleton_##n;

#define MAKE_SINGLETON_SCOPED(T, n, init, scope) \
    inline T _singleton_##n = init; \
    inline T *scope##_##n = &_singleton_##n;

