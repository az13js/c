/**
 * 将文件的内容全部读取到内存的一个连续区域上面
 */
#include <stdio.h>
#include "memory_file.h"
#include <stdlib.h>

int main(int argc, char *argv[])
{
    struct memory_file m = memory_file_from("train-images-idx3-ubyte/train-images.idx3-ubyte");
    memory_file_show_error_info(m);
    printf("destory=%d\n", memory_file_destory(m));
    return 0;
}
