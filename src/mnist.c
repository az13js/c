#include "mnist.h"

struct mnist mnist_create()
{
    struct mnist data;
    data.images = memory_file_from("train-images-idx3-ubyte/train-images.idx3-ubyte");
    data.labels = memory_file_from("train-labels-idx1-ubyte/train-labels.idx1-ubyte");
    data.have_error = data.labels.error || data.images.error;
    if (data.have_error) {
        memory_file_destory(data.images);
        memory_file_destory(data.labels);
    } else {
        if (0 == mnist_count(data)) {
            data.have_error = 1;
        }
    }
    return data;
}

unsigned char mnist_destory(struct mnist data)
{
    memory_file_destory(data.images);
    memory_file_destory(data.labels);
    if (data.have_error) {
        return 1;
    }
    return 0;
}

unsigned int mnist_count(struct mnist data)
{
    unsigned int images_count, labels_count;
    images_count = 0;
    images_count = (images_count | data.images.memory_pointer[4]) << (3 * 8);
    images_count = (images_count | data.images.memory_pointer[5]) << (2 * 8);
    images_count = (images_count | data.images.memory_pointer[6]) << (1 * 8);
    images_count = images_count | data.images.memory_pointer[7];
    labels_count = 0;
    labels_count = (labels_count | data.labels.memory_pointer[4]) << (3 * 8);
    labels_count = (labels_count | data.labels.memory_pointer[5]) << (2 * 8);
    labels_count = (labels_count | data.labels.memory_pointer[6]) << (1 * 8);
    labels_count = labels_count | data.labels.memory_pointer[7];
    if (labels_count != images_count) {
        return 0;
    }
    return labels_count;
}

unsigned int mnist_image_row(struct mnist data)
{
    unsigned int row;
    row = 0;
    row = (row | data.images.memory_pointer[8]) << (3 * 8);
    row = (row | data.images.memory_pointer[9]) << (2 * 8);
    row = (row | data.images.memory_pointer[10]) << (1 * 8);
    row = row | data.images.memory_pointer[11];
    return row;
}

unsigned int mnist_image_column(struct mnist data)
{
    unsigned int column;
    column = 0;
    column = (column | data.images.memory_pointer[12]) << (3 * 8);
    column = (column | data.images.memory_pointer[13]) << (2 * 8);
    column = (column | data.images.memory_pointer[14]) << (1 * 8);
    column = column | data.images.memory_pointer[15];
    return column;
}

unsigned char* mnist_get_image_data(struct mnist data, unsigned int index)
{
    unsigned int key;
    if (index <= 0 || index > mnist_count(data)) {
        return NULL;
    }
    key = 16;
    key = key + (index - 1) * sizeof(unsigned char);
    return &(data.images.memory_pointer[key]);
}

unsigned char mnist_get_label_data(struct mnist data, unsigned int index)
{
    unsigned int key;
    if (index <= 0 || index > mnist_count(data)) {
        return 0;
    }
    key = 8;
    key = key + (index - 1) * sizeof(unsigned char);
    return data.labels.memory_pointer[key];
}
