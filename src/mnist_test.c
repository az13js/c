#include "mnist.h"

int main(int argc, char *argv[])
{
    int i;
    struct mnist data;
    data = mnist_create();
    printf("count: %d\n", mnist_count(data));
    printf("row: %d\n", mnist_image_row(data));
    printf("column: %d\n", mnist_image_column(data));
    for (i = 0; i < 10; i++) {
        printf("label: %d\n", mnist_get_label_data(data, (unsigned int)(i + 1)));
    }
    mnist_destory(data);
    return 0;
}
