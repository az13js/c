#include "memory_file.h"

int memory_file_destory(struct memory_file m_file)
{
    if (0 == m_file.error && NULL != m_file.memory_pointer) {
        free(m_file.memory_pointer);
        return 0;
    } else {
        return -1;
    }
}

int memory_file_show_error_info(struct memory_file m_file)
{
    if (0 == m_file.error) {
        printf("No error happend.\n");
        printf("memory_pointer=%d\n", m_file.memory_pointer);
        printf("file_size_byte=%d\n", m_file.file_size_byte);
        return 0;
    }
    if (1 == m_file.error) {
        printf("file name error\n");
        return 0;
    }
    if (2 == m_file.error) {
        printf("open file fail\n");
        return 0;
    }
    if (3 == m_file.error) {
        printf("fseek fail\n");
        return 0;
    }
    if (4 == m_file.error) {
        printf("file size <= 0\n");
        return 0;
    }
    if (5 == m_file.error) {
        printf("malloc fail.\n");
        return 0;
    }
    if (6 == m_file.error) {
        printf("fread fail.\n");
        return 0;
    }
    if (7 == m_file.error) {
        printf("fclose fail.\n");
        return 0;
    }
    return -1;
}

/**
 * 根据指定的文件名，打卡文件。然后把文件的全部字节读取到内存。
 * 然后关闭文件，返回MemoryFile。
 *
 * Author: az13js
 * 2019/5/1
 */
struct memory_file memory_file_from(char* file_name)
{
    FILE* file_pointer;
    unsigned int file_size_byte;
    unsigned char* memory_pointer;
    struct memory_file a_memory_file;

    a_memory_file.memory_pointer = 0;
    a_memory_file.file_size_byte = 0;
    a_memory_file.error = 0;

    if (!file_name) {
        a_memory_file.error = 1;
        return a_memory_file;
    }

    if (!(file_pointer = fopen(file_name, "rb"))) {
        a_memory_file.error = 2;
        return a_memory_file;
    }

    if (fseek(file_pointer, 0, SEEK_END)) {
        fclose(file_pointer);
        a_memory_file.error = 3;
        return a_memory_file;
    }

    if ((file_size_byte = ftell(file_pointer)) <= 0) {
        fclose(file_pointer);
        a_memory_file.error = 4;
        return a_memory_file;
    }

    if (!(memory_pointer = (unsigned char*)malloc(file_size_byte))) {
        fclose(file_pointer);
        a_memory_file.error = 5;
        return a_memory_file;
    }

    if (fread(memory_pointer, 1, file_size_byte, file_pointer)) {
        fclose(file_pointer);
        free(memory_pointer);
        a_memory_file.error = 6;
        return a_memory_file;
    }

    if (0 != fclose(file_pointer)) {
        free(memory_pointer);
        a_memory_file.error = 7;
        return a_memory_file;
    }
    a_memory_file.memory_pointer = memory_pointer;
    a_memory_file.file_size_byte = file_size_byte;
    return a_memory_file;
}

int memory_file_save_as(struct memory_file m_file, char* file_name)
{
    FILE* file_pointer;

    if (m_file.error) {
        return 2;
    }

    if (!file_name) {
        return 1;
    }

    if (!(file_pointer = fopen(file_name, "wb"))) {
        return 3;
    }

    if (m_file.file_size_byte != fwrite(m_file.memory_pointer, 1, m_file.file_size_byte, file_pointer)) {
        fclose(file_pointer);
        return 4;
    }
    fclose(file_pointer);
    return 0;
}
