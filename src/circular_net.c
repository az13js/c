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
    printf("Circular net dump:\n");
    printf("================================================================================\n");
    printf("Circular net error info:\n");
    printf("  Have error value: %d\n", net.have_error);
    printf("  Error message: \"%s\"\n", net.error_message);
    if (!net.have_error) {
        printf("No error, weights and derivatives:\n");
        for (layer = 0; layer < net.layer_number - 1; layer++) {
            printf("  Layer %d:\n", layer + 2);
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
        printf("Outputs:\n");
        for (layer = 0; layer < net.layer_number; layer++) {
            printf("  Layer %d:\n", layer + 1);
            for (cell = 0; cell < net.structure[layer]; cell++) {
                printf("    %lf\t", net.outputs[layer][cell]);
            }
            printf("\n");
        }
    }
    printf("================================================================================\n");
    printf("Dump info finish.\n");
}

// 给定输入和输出缓冲区，计算
unsigned char circular_net_run(
    struct circular_net net,
    double* input,
    double* output
) {
    int layer, cell, weight_index;
    double* input_pointer;
    double* output_pointer;
    if (!input) {
        return 1;
    }
    if (!output) {
        return 2;
    }
    if (net.have_error) {
        return 3;
    }
    input_pointer = net.outputs[0];
    output_pointer = net.outputs[net.layer_number - 1];
    net.outputs[0] = input;
    net.outputs[net.layer_number - 1] = output;
    circular_net_just_run(net);
    net.outputs[0] = input_pointer;
    net.outputs[net.layer_number - 1] = output_pointer;
    return 0;
}

// 计算
unsigned char circular_net_just_run(struct circular_net net) {
    int layer, cell, weight_index;
    double differ;
    if (net.have_error) {
        return 3;
    }
    for (layer = 1; layer < net.layer_number; layer++) {
        for (cell = 0; cell < net.structure[layer]; cell++) {
            net.outputs[layer][cell] = 0.0;
            for (weight_index = 0; weight_index < net.structure[layer - 1]; weight_index++) {
                differ = net.outputs[layer - 1][weight_index] - net.weight[layer - 1][cell][weight_index];
                net.outputs[layer][cell] += differ * differ;
            }
            net.outputs[layer][cell] = sqrt(net.outputs[layer][cell]);
        }
    }
    return 0;
}

// 运行网络，并进行反向梯度下降
unsigned char circular_net_fit(
    struct circular_net net,
    double* input,
    double* output,
    double lr
) {
    int layer, cell, weight_index, cell_next_layer;
    double derivative_sum_next_layer;
    double* input_pointer; // 用来保存网络输入原始指针
    if (!input) {
        return 1;
    }
    if (!output) {
        return 2;
    }
    if (net.have_error) {
        return 3;
    }
    // 保存原来的指针，然后将网络输入指向指定的input指针
    input_pointer = net.outputs[0];
    net.outputs[0] = input;
    circular_net_just_run(net);
    /*
     * 反向计算梯度。由于第一层没有，所以程序层数比实际层数少一层
     *
     * 这里计算梯度采用普通的平方差损失。计算误差的公式是：
     * E = 0.5 * SUM[(O - S)^2]
     * O 是网络输出单元的输出值，S是期望的正确输出值。
     * E对O的偏导数是：
     * dE/dO = O - S
     *
     * 圆单元的计算公式是：
     * O = sqrt{SUM[(x - w)^2]}
     * x是单元输出端，w是对应的输入端的权重。此公式的偏导数：
     * dO/dw = (w - x) / O
     * dO/dx = (x - w) / O
     * 两条偏导数的公式形式是一样的。它们互为对方的相反数。
     */
    for (layer = net.layer_number - 2; layer > -1; layer--) {
        if (layer == net.layer_number - 2) { // 最后一层直接计算
            for (cell = 0; cell < net.structure[layer + 1]; cell++) {
                for (weight_index = 0; weight_index < net.structure[layer]; weight_index++) {
                    if (0.0 == net.outputs[layer + 1][cell]) {
                        net.derivative[layer][cell][weight_index] = 0.0;
                    } else {
                        net.derivative[layer][cell][weight_index] = (net.outputs[layer + 1][cell] - output[cell]) * (net.weight[layer][cell][weight_index] - net.outputs[layer][weight_index]) / net.outputs[layer + 1][cell];
                    }
                }
            }
        } else { // 非最后一层的需要使用链式求导计算
            for (cell = 0; cell < net.structure[layer + 1]; cell++) {
                derivative_sum_next_layer = 0.0;
                for (cell_next_layer = 0; cell_next_layer < net.structure[layer + 2]; cell_next_layer++) {// layer+1是当前层，往后一层是layer+2
                    derivative_sum_next_layer -= net.derivative[layer + 1][cell_next_layer][cell]; // 两条偏导数互为相反数，对输入的偏导等于-1乘以对权重的偏导数
                }
                // 下面这步计算跟上面的计算差不多
                for (weight_index = 0; weight_index < net.structure[layer]; weight_index++) {
                    if (0 == net.outputs[layer + 1][cell]) {
                        net.derivative[layer][cell][weight_index] = 0.0;
                    } else {
                        net.derivative[layer][cell][weight_index] = derivative_sum_next_layer * (net.weight[layer][cell][weight_index] - net.outputs[layer][weight_index]) / net.outputs[layer + 1][cell];
                    }
                }
            }
        }
    }
    // 计算偏导数完成，下面进行梯度下降
    for (layer = 0; layer < net.layer_number - 1; layer++) {
        for (cell = 0; cell < net.structure[layer + 1]; cell++) {
            for (weight_index = 0; weight_index < net.structure[layer]; weight_index++) {
                net.weight[layer][cell][weight_index] -= lr * net.derivative[layer][cell][weight_index];
            }
        }
    }
    net.outputs[0] = input_pointer;
    return 0;
}

// 计算并返回方差
double circular_net_get_mse(struct circular_net net, double* input, double* output)
{
    double* input_pointer;
    double mse, diff;
    int i;
    if (net.have_error) {
        return -1;
    }
    if (!input) {
        return -2;
    }
    if (!output) {
        return -3;
    }
    input_pointer = net.outputs[0];
    net.outputs[0] = input;
    circular_net_just_run(net);
    mse = 0.0;
    for (i = 0; i < net.structure[net.layer_number - 1]; i++) {
        diff = net.outputs[net.layer_number - 1][i] - output[i];
        mse += diff * diff;
    }
    mse /= 2.0;
    net.outputs[0] = input_pointer;
    return mse;
}

double circular_net_get_batch_avg_mse(
    struct circular_net net,
    double** inputs,
    double** outputs,
    unsigned int batch_size
) {
    double mse, singled;
    int i;
    if (net.have_error) {
        return -1;
    }
    if (!inputs) {
        return -2;
    }
    if (!outputs) {
        return -3;
    }
    mse = 0.0;
    for (i = 0; i < batch_size; i++) {
        if ((singled = circular_net_get_mse(net, inputs[i], outputs[i])) < 0.0) {
            return -4;
        }
        mse += singled;
    }
    return mse / batch_size;
}

// 训练一批数据1次
unsigned char circular_net_fit_batch(
    struct circular_net net,
    double** inputs,
    double** outputs,
    unsigned int batch_size,
    double lr
) {
    int i;
    if (net.have_error) {
        return 1;
    }
    if (!inputs) {
        return 2;
    }
    if (!outputs) {
        return 3;
    }
    for (i = 0; i < batch_size; i++) {
        if (circular_net_fit(net, inputs[i], outputs[i], lr)) {
            return 4;
        }
    }
    return 0;
}
