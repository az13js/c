#ifndef CIRCULAR_NET

#define CIRCULAR_NET

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

struct circular_net
{
    unsigned int layer_number; // 层数
    unsigned int* structure; // 结构数组
    double** outputs; // 单元的输出值
    double*** weight; // 圆心坐标，权重
    double*** derivative; // 偏导数
    unsigned char have_error; // 是否出现错误
    char* error_message; // 错误信息
};

// 创建网络
struct circular_net circular_net_create(unsigned int layer_number, unsigned int *structure);
// 随机设置全部的权重
unsigned char circular_net_random_weight(struct circular_net net, double min, double max);
// 打印所有的数据，用于调试
void circular_net_dump(struct circular_net net);
// 运行网络，得到数据。缓冲区请自行准备
unsigned char circular_net_run(struct circular_net net, double* input, double* output);
// 运行网络，并进行反向梯度下降
unsigned char circular_net_fit(struct circular_net net, double* input, double* output, double lr);
// 计算
unsigned char circular_net_just_run(struct circular_net net);

#endif
