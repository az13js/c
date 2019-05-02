#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE* file_pointer = fopen("fread_to_pointer.c", "rb");
    char* buffer;
    buffer = (char*)malloc(20);
    fread(buffer, 1, 19, file_pointer);
    fclose(file_pointer);
    buffer[19] = '\0';
    printf("buffer is:\n%s\n", buffer);
    return 0;
}
