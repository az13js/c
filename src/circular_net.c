#include "circular_net.h"

// 创建网络
struct circular_net circular_net_create(
    unsigned int layer_number,
    unsigned int *structure
) {
    int i, j, k, l;
    struct circular_net net;

    net.layer_number  = 0;
    net.structure     = NULL;
    net.outputs       = NULL;
    net.weight        = NULL;
    net.derivative    = NULL;
    net.have_error    = 0;
    net.error_message = "\0";

    if (layer_number < 1) {
        net.have_error = 1;
        net.error_message = "layer_number must >= 2.\0";
        return net;
    }

    if (!structure) {
        net.have_error = 1;
        net.error_message = "structure pointer is NULL.\0";
        return net;
    }
    net.layer_number = layer_number;
    net.structure = (unsigned int*)calloc(sizeof (unsigned int), layer_number);
    if (!net.structure) {
        net.have_error = 1;
        net.error_message = "init structure, calloc fail.\0";
        return net;
    }

    for (i = 0; i < layer_number; i++) {
        net.structure[i] = structure[i];
    }
    // 初始化输出
    net.outputs = (double**)calloc(sizeof (double*), layer_number);
    if (!net.outputs) {
        net.have_error = 1;
        net.error_message = "init outputs, calloc fail.\0";
        free(net.structure);
        return net;
    }
    for (i = 0; i < layer_number; i++) {
        net.outputs[i] = (double*)calloc(sizeof (double), structure[i]);
        if (!net.outputs[i]) {
            for (j = 0; j < i; j++) {
                free(net.outputs[j]);
            }
            free(net.outputs);
            free(net.structure);
            net.have_error = 1;
            net.error_message = "init outputs-values, calloc fail.\0";
            return net;
        }
    }
    // 初始化权重值
    net.weight = (double***)calloc(sizeof (double**), layer_number - 1);
    if (!net.weight) {
        net.have_error = 1;
        net.error_message = "init weight, calloc fail.\0";
        for (i = 0; i < layer_number; i++) {
            free(net.outputs[i]);
        }
        free(net.outputs);
        free(net.structure);
        return net;
    }
    for (i = 0; i < layer_number - 1; i++) {
        net.weight[i] = (double**)calloc(sizeof (double*), structure[i + 1]);
        if (!net.weight[i]) {
            // 发生错误，释放所有层的权重
            for (j = 0; j < i; j++) {
                for (k = 0; k < structure[j + 1]; k++) {
                    free(net.weight[j][k]); // 释放第j层第k个单元的权重数组
                }
                free(net.weight[j]);
            }
            free(net.weight);
            for (j = 0; j < layer_number; j++) {
                free(net.outputs[j]); // 释放每一层的输出值
            }
            free(net.outputs);
            free(net.structure);
            net.have_error = 1;
            net.error_message = "init weight-values, calloc fail.\0";
            return net;
        }
        // 初始化里面的每个单元的权重数组
        for (j = 0; j < structure[i]; j++) {
            net.weight[i][j] = (double*)calloc(sizeof (double), structure[i]);
            if (!net.weight[i][j]) {
                for (k = 0; k < j; k++) { // 释放当前层所有单元的权重
                    free(net.weight[i][k]);
                }
                free(net.weight[i]);
                // 释放前面全部层每一层的单元的权重
                for (l = 0; l < i; l++) {
                    for (k = 0; k < structure[l + 1]; k++) {
                        free(net.weight[l][k]);
                    }
                    free(net.weight[l]);
                }
                free(net.weight);
                for (k = 0; k < layer_number; k++) {
                    free(net.outputs[k]); // 释放每一层的输出值
                }
                free(net.outputs);
                free(net.structure);
                net.have_error = 1;
                net.error_message = "init weight-values, calloc fail.\0";
                return net;
            }
        }
    }

    // 初始化偏导数
    net.derivative = (double***)calloc(sizeof (double**), layer_number - 1);
    if (!net.derivative) {
        net.have_error = 1;
        net.error_message = "init derivative, calloc fail.\0";

        // 释放权重所占的内存
        for (i = 0; i < layer_number - 1; i++) {
            for (j = 0; j < structure[i + 1]; j++) {
                free(net.weight[i][j]);
            }
            free(net.weight[i]);
        }
        free(net.weight);

        for (i = 0; i < layer_number; i++) {
            free(net.outputs[i]);
        }
        free(net.outputs);
        free(net.structure);
        return net;
    }
    for (i = 0; i < layer_number - 1; i++) {
        net.derivative[i] = (double**)calloc(sizeof (double*), structure[i + 1]);
        if (!net.derivative[i]) {
            // 发生错误，释放所有层的偏倒数
            for (j = 0; j < i; j++) {
                for (k = 0; k < structure[j + 1]; k++) {
                    free(net.derivative[j][k]); // 释放第j层第k个单元的偏导数数组
                }
                free(net.derivative[j]);
            }
            free(net.derivative);

            // 释放权重所占的内存
            for (k = 0; k < layer_number - 1; k++) {
                for (j = 0; j < structure[k + 1]; j++) {
                    free(net.weight[k][j]);
                }
                free(net.weight[k]);
            }
            free(net.weight);

            for (j = 0; j < layer_number; j++) {
                free(net.outputs[j]); // 释放每一层的输出值
            }
            free(net.outputs);
            free(net.structure);
            net.have_error = 1;
            net.error_message = "init derivative-values, calloc fail.\0";
            return net;
        }
        // 初始化里面的每个单元的偏导数数组
        for (j = 0; j < structure[i]; j++) {
            net.derivative[i][j] = (double*)calloc(sizeof (double), structure[i]);
            if (!net.derivative[i][j]) {
                // 释放权重所占的内存
                for (k = 0; k < layer_number - 1; k++) {
                    for (l = 0; l < structure[k + 1]; l++) {
                        free(net.weight[k][l]);
                    }
                    free(net.weight[k]);
                }
                free(net.weight);

                for (k = 0; k < j; k++) { // 释放当前层所有单元的偏导数
                    free(net.derivative[i][k]);
                }
                free(net.derivative[i]);
                // 释放前面全部层每一层的单元的偏导数
                for (l = 0; l < i; l++) {
                    for (k = 0; k < structure[l + 1]; k++) {
                        free(net.derivative[l][k]);
                    }
                    free(net.derivative[l]);
                }
                free(net.derivative);
                for (k = 0; k < layer_number; k++) {
                    free(net.outputs[k]); // 释放每一层的输出值
                }
                free(net.outputs);
                free(net.structure);
                net.have_error = 1;
                net.error_message = "init derivative-values, calloc fail.\0";
                return net;
            }
        }
    }
    return net;
}

// 随机设置全部的权重
unsigned char circular_net_random_weight(
    struct circular_net net,
    double min,
    double max
) {
    int layer, cell, weight_index;
    if (net.have_error) {
        return 1;
    }
    if (min > max) {
        return 2;
    }
    for (layer = 0; layer < net.layer_number - 1; layer++) {
        for (cell = 0; cell < net.structure[layer + 1]; cell++) {
            for (weight_index = 0; weight_index < net.structure[layer]; weight_index++) {
                net.weight[layer][cell][weight_index] = (double)rand() / RAND_MAX * (max - min) + min;
            }
        }
    }
    return 0;
}

// 打印所有的数据，用于调试
void circular_net_dump(struct circular_net net)
{
    int layer, cell, weight_index;
    printf("Circular net error info:\n");
    printf("  Have error value: %d\n", net.have_error);
    printf("  Error message: \"%s\"\n", net.error_message);
    if (!net.have_error) {
        printf("Circular net no error, print weights and derivatives.\n");
        for (layer = 0; layer < net.layer_number - 1; layer++) {
            printf("  Layer %d:\n", layer + 1);
            for (cell = 0; cell < net.structure[layer + 1]; cell++) {
                printf("    Cell %d, weights:\n      ", cell + 1);
                for (weight_index = 0; weight_index < net.structure[layer]; weight_index++) {
                    printf("%lf\t", net.weight[layer][cell][weight_index]);
                }
                printf("\n");
                printf("    Cell %d, derivatives:\n      ", cell + 1);
                for (weight_index = 0; weight_index < net.structure[layer]; weight_index++) {
                    printf("%lf\t", net.derivative[layer][cell][weight_index]);
                }
                printf("\n");
            }
        }
    }
    printf("Dump info finish.\n");
}
