#!/bin/bash

apt-get install -y make cmake
apt-get install -y libgtest-dev
cd /usr/src/gtest
cmake CMakeLists.txt
make
cp *.a /usr/lib