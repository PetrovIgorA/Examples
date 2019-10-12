# Tools for running

Before tools installing please run:
```shell
$ sudo apt-get update
```

## make
```shell
$ sudo apt-get install make -y
```

## cmake

Firstly, install default cmake version:
```shell
$ sudo apt-get install cmake -y
```

If you want newer version then after default cmake installing (cmake 3.16.5 usage for example) download [archive](https://github.com/Kitware/CMake/releases/download/v3.16.5/cmake-3.16.5.tar.gz) from [offical site](https://cmake.org/download/) and run next:
```shell
$ tar -xzvf cmake-3.16.5.tar.gz
$ sudo mv cmake-3.16.5 /opt/cmake-3.16.5 && cd /opt/cmake-3.16.5
$ sudo cmake .
$ sudo make
$ sudo make install
```

## Google test
For `gtest` installing run:
```shell
$ sudo apt-get install libgtest-dev
$ cd /usr/src/gtest
$ sudo cmake CMakeLists.txt
$ sudo make
$ sudo cp *.a /usr/lib
```