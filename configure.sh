#!/bin/bash

# Install default make and cmake
apt-get install -y make cmake

# Install gtest
apt-get install -y libgtest-dev
cd /usr/src/gtest
cmake CMakeLists.txt
make
cp *.a /usr/lib
