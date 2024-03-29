#include "str.h"

str_t str_new() {
    str_t str = {
        .str = NULL,
        .len = 0,
    };
    return str;
}

#define nstr(s) str_news(s)
str_t str_news(char* s) {
    str_t str = STR_INIT();
    str.str = calloc(strlen(s), sizeof(char));
    memcpy(str.str, s, strlen(s));
    str.len = strlen(s);
    return str;
}

void str_append(str_t *str, char* s, int len) {
    if (s == NULL) return;

    char* new_str = (char*) realloc(str->str, str->len + len);
    if (new_str == NULL) return;

    memcpy(&new_str[str->len], s, len);
    str->str = new_str;
    str->len += len;
}

void str_appends(str_t *str, char* s) {
    if (s == NULL) return;
    str_append(str, s, strlen(s));
}

void str_appendf(str_t *str, char* fmt, ...) {
    va_list args;
    va_start(args, fmt);

    const int buf_len = 1024;
    char buf[buf_len];
    memset(buf, 0, buf_len); // 0 out buf
    vsprintf(buf, fmt, args);

    va_end(args);

    str_append(str, buf, strlen(buf));
}

void str_end(str_t* str, ...) {
    if (str->str != NULL) {
        str_append(str, "\0", 1);
    }

    va_list args;
    va_start(args, str);

    str_t *s;
    while ((s = va_arg(args, str_t*)) != NULL) {
        if (s->str != NULL) {
            str_append(str, "\0", 1);
        }
    }

    va_end(args);
}

void str_clear(str_t* str, ...) {
    if (str->str != NULL) {
        free(str->str);
        str->str = NULL;
        str->len = 0;
    }

    va_list args;
    va_start(args, str);

    str_t *s;
    while ((s = va_arg(args, str_t*)) != NULL) {
        if (s->str != NULL) {
            free(s->str);
            s->str = NULL;
            s->len = 0;
        }
    }

    va_end(args);
}

void str_cpy(str_t* dst, str_t* src, size_t len) {
    if (dst == NULL || src == NULL || (len == 0 && src->len == 0)) return;
    dst->len = src->len;
    memcpy(dst->str, src->str, (len > 0) ? len : src->len);
}

void str_free(str_t *str, ...) {
    if (str->str != NULL) {
        free(str->str);
    }

    va_list args;
    va_start(args, str);

    str_t *s;
    while ((s = va_arg(args, str_t*)) != NULL) {
        if (s->str != NULL) {
            free(s->str);
        }
    }

    va_end(args);
}
