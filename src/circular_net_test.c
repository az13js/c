#include "circular_net.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int layers = 3;
    int structure[3] = {3, 2, 1};
    struct circular_net net;
    net = circular_net_create(layers, structure);
    circular_net_random_weight(net, -1.0, 2.0);
    circular_net_dump(net);
    return 0;
}
