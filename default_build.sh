#!/bin/bash

# Remove for rebuild
if [ -d build ]
then
rm -rf build
fi

# Building
mkdir build && cd build
cmake .. && make -j
