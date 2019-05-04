#include "circular_net.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    int i, j;
    int structure[3] = {2, 2, 1};
    double a[4][2] = {{0,0}, {0,1}, {1,0}, {1,1}};
    double b[4][1] = {{0}, {1}, {1}, {0}};
    double** inputs;
    double** outputs;
    struct circular_net net;
    inputs = (double**)calloc(sizeof (double*), 4);
    outputs = (double**)calloc(sizeof (double*), 4);
    for (i = 0; i < 4; i++) {
        inputs[i] = (double*)calloc(sizeof (double), 2);
        outputs[i] = (double*)calloc(sizeof (double), 1);
        for (j = 0; j < 2; j++) {
            inputs[i][j] = a[i][j];
        }
        outputs[i][0] = b[i][0];
    }
    net = circular_net_create(3, structure);
    circular_net_random_weight(net, -0.5, 0.5);
    printf("%.9lf\n", circular_net_get_batch_avg_mse(net, inputs, outputs, 4));
    for (i = 0; i < 500; i++) {
        //for (j = 0; j < 4; j++) {
        //    circular_net_fit(net, inputs[j], outputs[j], 0.5);
        //}
        circular_net_fit_batch(net, inputs, outputs, 4, 0.5);
        printf("%d,%.9lf\n", (i + 1), circular_net_get_batch_avg_mse(net, inputs, outputs, 4));
    }
    return 0;
}
