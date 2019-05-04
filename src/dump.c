#include <stdio.h>
#include "memory_file.h"

int main(int argc, char *argv[])
{
    int i;
    struct memory_file bin;
    bin = memory_file_from("dump.c");
    for (i = 0; i < bin.file_size_byte; i++) {
        printf("%d,0x%X,%d\n", i, bin.memory_pointer[i], bin.memory_pointer[i]);
    }
    memory_file_destory(bin);
    return 0;
}




