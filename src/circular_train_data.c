#include "circular_train_data.h"

struct circular_train_data circular_train_data_create_random(
    unsigned int total,
    unsigned int input_num,
    unsigned int output_num
) {
    int i, j;
    struct circular_train_data data;
    data.inputs        = NULL;
    data.outputs       = NULL;
    data.total         = total;
    data.input_num     = input_num;
    data.output_num    = output_num;
    data.have_error    = 0;
    data.error_message = "\0";

    data.inputs = (double**)calloc(total, sizeof (double*));
    if (!data.inputs) {
        data.have_error = 1;
        data.error_message = "calloc fail.\0";
        return data;
    }
    data.outputs = (double**)calloc(total, sizeof (double*));
    if (!data.outputs) {
        free(data.inputs);
        data.have_error = 1;
        data.error_message = "calloc fail.\0";
        return data;
    }

    for (i = 0; i < total; i++) {
        data.inputs[i] = (double*)calloc(input_num, sizeof (double));
        if (!data.inputs[i]) {
            for (j = 0; j < i; j++) {
                free(data.inputs[j]);
                free(data.outputs[j]);
            }
            free(data.inputs);
            free(data.outputs);
            data.have_error = 1;
            data.error_message = "calloc fail.\0";
            return data;
        }

        data.outputs[i] = (double*)calloc(output_num, sizeof (double));
        if (!data.outputs[i]) {
            for (j = 0; j < i; j++) {
                free(data.inputs[j]);
                free(data.outputs[j]);
            }
            free(data.inputs[j]);
            free(data.inputs);
            free(data.outputs);
            data.have_error = 1;
            data.error_message = "calloc fail.\0";
            return data;
        }

        for (j = 0; j < input_num; j++) {
            data.inputs[i][j] = (double)rand() / RAND_MAX * 2.0 - 1.0;
        }
        for (j = 0; j < output_num; j++) {
            data.outputs[i][j] = (double)rand() / RAND_MAX * 2.0 - 1.0;
        }
    }
    return data;
}

unsigned char circular_train_data_print(struct circular_train_data data) {
    int i, j;
    if (data.have_error) {
        printf("Error: %s\n", data.error_message);
        return 1;
    }
    if (0 == data.total) {
        printf("No data.\n");
    }

    for (i = 0; i < data.total; i++) {

        printf("(%d) inputs:", i + 1);
        for (j = 0; j < data.input_num; j++) {
            printf(" %e", data.inputs[i][j]);
        }
        printf("\n");

        printf("(%d) outputs:", i + 1);
        for (j = 0; j < data.output_num; j++) {
            printf(" %e", data.outputs[i][j]);
        }
        printf("\n");
    }
    return 0;
}

unsigned char circular_train_data_save(struct circular_train_data data, char* file)
{
    FILE* file_pointer;
    int i;
    if (data.have_error) {
        return 1;
    }
    file_pointer = fopen(file, "wb");
    if (!file_pointer) {
        return 2;
    }
    if (1 != fwrite(&(data.total), sizeof (unsigned int), 1, file_pointer)) {
        fclose(file_pointer);
        return 3;
    }
    if (1 != fwrite(&(data.input_num), sizeof (unsigned int), 1, file_pointer)) {
        fclose(file_pointer);
        return 4;
    }
    if (1 != fwrite(&(data.output_num), sizeof (unsigned int), 1, file_pointer)) {
        fclose(file_pointer);
        return 5;
    }
    for (i = 0; i < data.total; i++) {
        if (data.input_num != fwrite(data.inputs[i], sizeof (double), data.input_num, file_pointer)) {
            fclose(file_pointer);
            return 6;
        }
        if (data.output_num != fwrite(data.outputs[i], sizeof (double), data.output_num, file_pointer)) {
            fclose(file_pointer);
            return 7;
        }
    }
    fclose(file_pointer);
    return 0;
}

struct circular_train_data circular_train_data_create_from_file(char* file)
{
    int i, j;
    FILE* file_pointer;
    struct circular_train_data data;

    data.inputs        = NULL;
    data.outputs       = NULL;
    data.total         = 0;
    data.input_num     = 0;
    data.output_num    = 0;
    data.have_error    = 0;
    data.error_message = "\0";

    file_pointer = fopen(file, "rb");
    if (!file_pointer) {
        data.have_error = 1;
        data.error_message = "open file fail.\0";
        return data;
    }
    if (1 != fread(&(data.total), sizeof (unsigned int), 1, file_pointer)) {
        fclose(file_pointer);
        data.have_error = 1;
        data.error_message = "read data fail.\0";
        return data;
    }
    if (1 != fread(&(data.input_num), sizeof (unsigned int), 1, file_pointer)) {
        fclose(file_pointer);
        data.have_error = 1;
        data.error_message = "read data fail.\0";
        return data;
    }
    if (1 != fread(&(data.output_num), sizeof (unsigned int), 1, file_pointer)) {
        fclose(file_pointer);
        data.have_error = 1;
        data.error_message = "read data fail.\0";
        return data;
    }

    data.inputs = (double**)calloc(data.total, sizeof (double*));
    if (!data.inputs) {
        fclose(file_pointer);
        data.have_error = 1;
        data.error_message = "calloc fail.\0";
        return data;
    }
    data.outputs = (double**)calloc(data.total, sizeof (double*));
    if (!data.outputs) {
        fclose(file_pointer);
        free(data.inputs);
        data.have_error = 1;
        data.error_message = "calloc fail.\0";
        return data;
    }

    for (i = 0; i < data.total; i++) {
        data.inputs[i] = (double*)calloc(data.input_num, sizeof (double));
        if (!data.inputs[i]) {
            for (j = 0; j < i; j++) {
                free(data.inputs[j]);
                free(data.outputs[j]);
            }
            free(data.inputs);
            free(data.outputs);
            data.have_error = 1;
            data.error_message = "calloc fail.\0";
            fclose(file_pointer);
            return data;
        }

        if (data.input_num != fread(data.inputs[i], sizeof (double), data.input_num, file_pointer)) {
            for (j = 0; j < i; j++) {
                free(data.inputs[j]);
                free(data.outputs[j]);
            }
            free(data.inputs);
            free(data.outputs);
            data.have_error = 1;
            data.error_message = "read data fail.\0";
            fclose(file_pointer);
            return data;
        }

        data.outputs[i] = (double*)calloc(data.output_num, sizeof (double));
        if (!data.outputs[i]) {
            for (j = 0; j < i; j++) {
                free(data.inputs[j]);
                free(data.outputs[j]);
            }
            free(data.inputs[j]);
            free(data.inputs);
            free(data.outputs);
            data.have_error = 1;
            data.error_message = "calloc fail.\0";
            fclose(file_pointer);
            return data;
        }

        if (data.output_num != fread(data.outputs[i], sizeof (double), data.output_num, file_pointer)) {
            for (j = 0; j < i; j++) {
                free(data.inputs[j]);
                free(data.outputs[j]);
            }
            free(data.inputs[j]);
            free(data.inputs);
            free(data.outputs);
            data.have_error = 1;
            data.error_message = "read data fail.\0";
            fclose(file_pointer);
            return data;
        }
    }
    fclose(file_pointer);
    return data;
}

unsigned char circular_train_data_destory(struct circular_train_data data)
{
    int i;
    if (data.have_error) {
        return 1;
    }
    if (!data.inputs) {
        data.have_error = 1;
        data.error_message = "data.inputs pointer is NULL.\0";
        return 2;
    }
    if (!data.outputs) {
        data.have_error = 1;
        data.error_message = "data.outputs pointer is NULL.\0";
        return 3;
    }

    for (i = 0; i < data.total; i++) {
        if (!data.inputs[i]) {
            data.have_error = 1;
            data.error_message = "broken data.\0";
            return 4;
        }
        free(data.inputs[i]);
        if (!data.outputs[i]) {
            data.have_error = 1;
            data.error_message = "broken data.\0";
            return 5;
        }
        free(data.outputs[i]);
    }

    free(data.inputs);
    free(data.outputs);
    return 0;
}
