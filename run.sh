#!/bin/sh

cd src
gcc -O3 circular_net_mnist.c mnist.c memory_file.c circular_train_data.c circular_net.c -lm -o mnist.out
./mnist.out
