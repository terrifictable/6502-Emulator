#pragma once

#define _$0(f)
#define _$1(f, v) f(v)
#define _$2(f, v, ...) f(v) _$1(f, __VA_ARGS__)
#define _$3(f, v, ...) f(v) _$2(f, __VA_ARGS__)
#define _$4(f, v, ...) f(v) _$3(f, __VA_ARGS__)
#define _$5(f, v, ...) f(v) _$4(f, __VA_ARGS__)
#define _$6(f, v, ...) f(v) _$5(f, __VA_ARGS__)
#define _$7(f, v, ...) f(v) _$6(f, __VA_ARGS__)
#define _$8(f, v, ...) f(v) _$7(f, __VA_ARGS__)
#define _$9(f, v, ...) f(v) _$8(f, __VA_ARGS__)
#define _$10(f, v, ...) f(v) _$9(f, __VA_ARGS__)

#define _GET_MACRO(_0, _1, _2, _3, _4, _5, _6, _7, _8, _9, _10, n, ...) n
#define FOR_EACH(f, ...) _GET_MACRO(_0, __VA_ARGS__, _$10, _$9, _$8, _$7, _$6, _$5, _$4, _$3, _$2, _$1, _$0,)(f, __VA_ARGS__)


#define _ENUM_ELM_TO_STR_WITH_IDX(x, ...) [x] = #x,
#define MAKE_ENUM_STR(name, ...)   \
    const char* name[] = {         \
        FOR_EACH(_ENUM_ELM_TO_STR_WITH_IDX, __VA_ARGS__) \
    };

/* EXAMPLE USAGE:
 * > enum test { INFO, OK, WARNING, FAILED, TEST, X, Y, Z };
 * > MAKE_ENUM_STR(test_str, INFO, OK, WARNING, FAILED, TEST, X, Y, Z)
 * 
 * RESULT:
 * > const char* test_str[] = {
 * >     [INFO] = "INFO", 
 * >     [OK] = "OK",  
 * >     [WARNING] = "WARNING",  
 * >     [FAILED] = "FAILED",  
 * >     [TEST] = "TEST",  
 * >     [X] = "X",  
 * >     [Y] = "Y",  
 * >     [Z] = "Z",  
 * > };
 */
