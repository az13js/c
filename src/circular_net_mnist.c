#include "circular_net.h"
#include "mnist.h"
#include "circular_train_data.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    unsigned int* structure;
    unsigned int i, j;
    unsigned char* mnist_memory_file_pointer;
    struct mnist mnist_data;
    struct circular_train_data data;
    struct circular_net net;

    structure = (unsigned int*)calloc(3, sizeof (unsigned int));

    mnist_data = mnist_create();
    if (mnist_data.have_error) {
        printf("mnist data have error, exit.\n");
        return -1;
    }

    data = circular_train_data_create_random(mnist_count(mnist_data), mnist_image_row(mnist_data) * mnist_image_column(mnist_data), 10);
    if (data.have_error) {
        mnist_destory(mnist_data);
        printf("circular train data create fail, info: %s\n", data.error_message);
        return -2;
    }

    printf("memory load OK\n");

    for (i = 0; i < mnist_count(mnist_data); i++) {
        for (j = 0; j < 10; j++) {
            if (j == mnist_get_label_data(mnist_data, i + 1)) {
                data.outputs[i][j] = 1.0;
            } else {
                data.outputs[i][j] = 0.0;
            }
        }
        mnist_memory_file_pointer = mnist_get_image_data(mnist_data, i + 1);
        for (j = 0; j < mnist_image_row(mnist_data) * mnist_image_column(mnist_data); j++) {
            data.inputs[i][j] = (double)mnist_memory_file_pointer[j];
        }
    }

    printf("data transform ok\n");

    structure[0] = data.input_num;
    structure[1] = 29;
    structure[2] = data.output_num;
    printf("structure %d, %d, %d\n", structure[0], structure[1], structure[2]);
    net = circular_net_create(3, structure);

    if (net.have_error) {
        printf("create net error, info : %s\n", net.error_message);
        mnist_destory(mnist_data);
        circular_train_data_destory(data);
        return -3;
    }

    circular_net_random_weight(net, -0.05, 0.05);

    printf("MSE : %.9lf\n", circular_net_get_batch_avg_mse(net, data.inputs, data.outputs, data.total));
    for (i = 0; i < 200; i++) {
        circular_net_fit_batch(net, data.inputs, data.outputs, data.total, 0.01);
        printf("MSE : %.9lf\n", circular_net_get_batch_avg_mse(net, data.inputs, data.outputs, data.total));
    }

    circular_train_data_destory(data);
    return 0;
}
