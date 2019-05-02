#include <stdio.h>
#include "memory_file.h"

int main(int argc, char *argv[])
{
    int i;
    struct memory_file m = memory_file_from("file_read.c");
    printf("This is program \"read_file_print\".\n");
    memory_file_show_error_info(m);
    printf("memory_file_save_as:%d\n", memory_file_save_as(m, "save.out"));
    memory_file_destory(m);
    return 0;
}
