#include "circular_net.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int structure[3] = {2, 2, 1};
    int i;
    struct circular_net net;
    double input[2] = {1.0, 0.0};
    double output[1] = {1.0};
    net = circular_net_create(3, structure);
    circular_net_random_weight(net, -0.5, 0.5);
    circular_net_fit(net, input, output, 0.0);
    circular_net_dump(net);
    for (i = 0; i < 40000000; i++) {
        circular_net_fit(net, input, output, 0.1);
    }
    circular_net_dump(net);
    return 0;
}
