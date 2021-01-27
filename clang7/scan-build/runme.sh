#!/bin/bash

cd sample
rm -rf result
make clean
scan-build -o result make

scan-view --no-browser --allow-all-hosts --host 192.168.2.200 $(pwd)/result/*

make clean
rm -rf result