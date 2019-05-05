/**
 * 将文件的内容全部读取到内存的一个连续区域上面
 */
#ifndef AZ13JS_MNIST

#define AZ13JS_MNIST

#include "memory_file.h"

struct mnist {
    struct memory_file images;
    struct memory_file labels;
    unsigned char have_error;
};

struct mnist mnist_create();
unsigned char mnist_destory(struct mnist data);
unsigned int mnist_count(struct mnist data);
unsigned int mnist_image_row(struct mnist data);
unsigned int mnist_image_column(struct mnist data);
unsigned char* mnist_get_image_data(struct mnist data, unsigned int index);
unsigned char mnist_get_label_data(struct mnist data, unsigned int index);

#endif
