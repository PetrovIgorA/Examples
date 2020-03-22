# C++ Examples

[![Build and Test](https://github.com/PetrovIgorA/Examples/workflows/Example_testing/badge.svg)](https://github.com/PetrovIgorA/Examples)

## Examples in project

### Function
Usage of math functions and operations(`+`, `-`, `*`, `/`) on them.

### Matrix
Matrix implementation.

## Configuration
For running tests you need install cmake and googletest.  
Manual installing is [here](docs/Installing.md) or use `configure.sh` for default configuration.

## Building
You can run `default_build.sh` for default build or use:
```shell
$ mkdir build_dir && cd build_dir
$ cmake [options ...] path/to/Examples
$ make [options ...]
```

## Run test
After building run test in `build` folder via:
```shell
$ make test
```
