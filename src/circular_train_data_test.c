#include <stdio.h>
#include "circular_train_data.h"

int main(int argc, char *argv[])
{
    struct circular_train_data data;
    data = circular_train_data_create_random(1000, 40000, 10);
    circular_train_data_save(data, "memory.out");
    getchar();
    circular_train_data_destory(data);
    getchar();
    getchar();
    return 0;
}
