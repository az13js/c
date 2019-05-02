/**
 * 将文件的内容全部读取到内存的一个连续区域上面
 */
#ifndef AZ13JS_MEMORY_FILE

#define AZ13JS_MEMORY_FILE

#include <stdio.h>
#include <stdlib.h>

struct memory_file
{
    unsigned char* memory_pointer;
    unsigned int file_size_byte;
    signed char error;
};

// 销毁内存文件
int memory_file_destory(struct memory_file m_file);
// 打印调试信息
int memory_file_show_error_info(struct memory_file m_file);
// 从文件创建内存文件
struct memory_file memory_file_from(char* file_name);
// save memory data as a file
int memory_file_save_as(struct memory_file m_file, char* file_name);

#endif