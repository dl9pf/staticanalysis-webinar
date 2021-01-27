#!/bin/bash

echo "#####################################"
echo "gcc-10 -fanalyzer -Wall nullpointer.c"
echo "#####################################"

gcc-10 -fanalyzer -Wall nullpointer.c

rm -rf a.out &
