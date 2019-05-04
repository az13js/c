#ifndef CIRCULAR_TRAIN_DATA

#define CIRCULAR_TRAIN_DATA

#include <stdlib.h>
#include <stdio.h>

struct circular_train_data
{
    double** inputs;
    double** outputs;
    unsigned int total;
    unsigned int input_num;
    unsigned int output_num;
    unsigned char have_error;
    char* error_message;
};

struct circular_train_data circular_train_data_create_random(unsigned int total, unsigned int input_num, unsigned int output_num);
unsigned char circular_train_data_print(struct circular_train_data data);
unsigned char circular_train_data_save(struct circular_train_data data, char* file);
struct circular_train_data circular_train_data_create_from_file(char* file);
unsigned char circular_train_data_destory(struct circular_train_data data);

#endif