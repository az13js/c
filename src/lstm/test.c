#include "lstmlib.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    struct lstmlib* lstm = lstmlib_create(10);
    printf("%s\n", lstmlib_get_error_message(lstm));
    lstmlib_fillx(lstm, 0.123123);
    lstmlib_printx(lstm);
    lstmlib_print_params(lstm);
    lstmlib_destory(lstm);
    return 0;
}
