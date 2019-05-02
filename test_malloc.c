#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int* arr;
    int x = 0;
    arr = calloc(sizeof x, 10);
    printf("pointer, arr, arr=%d\n", arr);

    for (x = 0; x < 10; x++) {
        arr[x] = 20 - x;
    }

    for (x = 0; x < 10; x++) {
        printf("%d ", arr[x]);
    }
    printf("\n");

    printf("finish\n");
    return 0;
}
