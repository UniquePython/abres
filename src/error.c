#include "abres/error.h"

#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

ABRES_Err *abres__error_new_loc(ABRES_ErrCode errcode, const char *file, int line, const char *fmt, ...)
{
    ABRES_Err *error = malloc(sizeof(ABRES_Err));
    if (!error)
        return NULL;

    error->errcode = errcode;
    error->file = file;
    error->line = line;
    error->cause = NULL;

    va_list args;
    va_start(args, fmt);
    if (vasprintf(&error->errmsg, fmt, args) < 0)
    {
        free(error);
        va_end(args);
        return NULL;
    }
    va_end(args);

    return error;
}

ABRES_Err *abres__error_wrap_loc(ABRES_ErrCode errcode, const char *file, int line, ABRES_Err *cause, const char *fmt, ...)
{
    ABRES_Err *error = malloc(sizeof(ABRES_Err));
    if (!error)
        return NULL;

    error->errcode = errcode;
    error->file = file;
    error->line = line;
    error->cause = cause;

    va_list args;
    va_start(args, fmt);
    if (vasprintf(&error->errmsg, fmt, args) < 0)
    {
        free(error);
        va_end(args);
        return NULL;
    }
    va_end(args);

    return error;
}

void abres_error_print(const ABRES_Err *error)
{
    if (error == NULL)
        return;

    const ABRES_Err *current = error;

    int indents = 0;

    while (current != NULL)
    {
        for (int i = 0; i < indents; i++)
            printf("\t");

        printf("[%s:%d] %s\n", current->file, current->line, current->errmsg);

        current = current->cause;

        indents++;
    }
}

void abres_error_free(ABRES_Err **error)
{
    if (error == NULL || *error == NULL)
        return;

    ABRES_Err *current = *error;
    ABRES_Err *next;
    while (current->cause != NULL)
    {
        next = current->cause;
        free(current->errmsg);
        free(current);
        current = next;
    }
    free(current->errmsg);
    free(current);
    *error = NULL;
}