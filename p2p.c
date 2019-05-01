#include <stdio.h>

int main()
{
    int number = 233;
    int* first_pointer;
    int** second_pointer;

    first_pointer = &number;
    second_pointer = &first_pointer;

    printf("second_pointer = %d\n", second_pointer);
    printf("*second_pointer = %d\n", *second_pointer);
    printf("**second_pointer = %d\n", **second_pointer);

    return 0;
}
