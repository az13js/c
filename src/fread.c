#include <stdio.h>

int main(int argc, char *argv[])
{
    FILE* file_pointer = fopen("fread.c", "r");
    char buffer[20];
    fread(buffer, 1, 19, file_pointer);
    fclose(file_pointer);
    buffer[19] = '\0';
    printf("buffer is:\n%s\n", buffer);
    return 0;
}
