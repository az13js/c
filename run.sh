#!/bin/sh

cd src/lstm/
gcc -O3 lstmlib.c test.c -lm -o lstm.out
./lstm.out
