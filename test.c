#include "abres/abres.h"
#include <stdio.h>

DEF_RESULT(int);

Result_int inner(int x)
{
    if (x < 0)
        return ERR(int, ABRES_NewErr(ABRES_INVAL, "x is negative: %d", x));
    return OK(int, x * 2);
}

Result_int outer(int x)
{
    TRY(int, int, val, inner(x), ABRES_INVAL, "outer failed");
    return OK(int, val);
}

int main(void)
{
    Result_int r = outer(-5);
    if (!IS_OK(r))
    {
        abres_error_print(r.error);
        abres_error_free(&r.error);
        return 1;
    }
    printf("value: %d\n", r.value);
    return 0;
}