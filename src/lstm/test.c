#include "lstmlib.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    struct lstmlib* lstm = lstmlib_create(1000);
    printf("%s\n", lstmlib_get_error_message(lstm));
    lstmlib_destory(lstm);
    return 0;
}
