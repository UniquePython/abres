#ifndef ABRES_RESULT_H
#define ABRES_RESULT_H

#include "error.h"

#include <stddef.h>

#define DEF_RESULT(T)     \
    typedef struct        \
    {                     \
        T value;          \
        ABRES_Err *error; \
    } Result_##T

#define OK(T, val) \
    (Result_##T) { .value = (val), .error = NULL }

#define ERR(T, err) \
    (Result_##T) { .value = (T){0}, .error = (err) }

#define IS_OK(err) ((err).error == NULL)

#define TRY(ReturnT, T, var, expr, wrap_code, ...)                                     \
    T var;                                                                             \
    do                                                                                 \
    {                                                                                  \
        Result_##T _r = (expr);                                                        \
        if (!IS_OK(_r))                                                                \
        {                                                                              \
            return ERR(ReturnT, ABRES_NewErrFrom(wrap_code, _r.error, ##__VA_ARGS__)); \
        }                                                                              \
        var = _r.value;                                                                \
    } while (0)

#endif