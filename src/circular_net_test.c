#include "circular_net.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int layers = 3, i;
    int structure[3] = {3, 2, 1};
    struct circular_net net;
    double input[3] = {1.1, 2.2, 3.3};
    double output[1] = {-1.1};
    net = circular_net_create(layers, structure);
    circular_net_random_weight(net, -1.0, 2.0);
    circular_net_dump(net);
    circular_net_run(net, input, output);
    printf("Input:\n");
    for (i = 0; i < 3; i++) {
        printf("%lf\t", input[i]);
    }
    printf("\nOutput:%lf\n", output[0]);
    circular_net_dump(net);
    return 0;
}
