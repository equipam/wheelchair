#!/bin/sh

# gcc driver.c -shared -o liblidar.so -g -Wall -Wl,-rpath=./ -L./ -lhps3d_arm

# cc -fPIC -shared -o liblidar.so driver.c -O3

gcc driver.c -o driver.out -g -Wall  -Wl,-rpath=./ -L./ -lhps3d_arm