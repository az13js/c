#include "circular_net.h"
#include <stdio.h>

int main(int argc, char *argv[])
{
    int layers = 3;
    int structure[3] = {3, 2, 1};
    struct circular_net net;
    net = circular_net_create(layers, structure);
    printf("%s, %d\n", net.error_message, net.have_error);
    return 0;
}
