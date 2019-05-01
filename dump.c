#include <stdio.h>
#include <stdlib.h>

struct MnistDataset
{
    unsigned char *fileName;
    unsigned int dataNumber;
    unsigned char input[];
};

int main(int argc, char *argv[])
{
    unsigned char* input;
    unsigned char c;
    input = calloc(100, sizeof c);
    printf("%d\n", sizeof input);
    return 0;
}




