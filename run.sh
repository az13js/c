#!/bin/sh

gcc-6 -lm -O3 main.c -o a.out
./a.out

gcc-6 -lm -O3 file_read.c memory_file.c -o file_read.out
./file_read.out

gcc-6 -lm -O3 prime.c -o prime.out
./prime.out

echo "math.c"
gcc-6 -lm -O3 math.c -o math.out
./math.out

echo "read_file_print.c"
gcc-6 -lm -O3 read_file_print.c memory_file.c -o read_file_print.out
./read_file_print.out