#include "eg.h"

int main(void)
{
    fnresult_t result = eg_single_window();
    if (result != FN_SUCCESS)
    {
        fputs("Debug: Example failed.\n", stderr);
        return result;
    }  

    fputs("Debug: Example succeeded.\n", stderr);

    return result;
}