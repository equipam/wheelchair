#!/bin/sh

g++ main.cpp ../lib/SerialInterface.cpp -o main.out -lserial

./main.out