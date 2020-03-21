# C++ Examples

[![Build and Test](https://github.com/PetrovIgorA/Examples/workflows/Example_testing/badge.svg)](https://github.com/PetrovIgorA/Examples/actions)

For running test you need install cmake and googletest.  
Manual installing is [here](docs/Installing.md).

### Function
Usage of math functions and operations(`+`, `-`, `*`, `/`) on them.

### Matrix
Matrix implementation.

## Run test
You can run `default_build.sh` for build or use:
```shell
$ mkdir build_dir && cd build_dir
$ cmake [options ...] path/to/Examples
$ make [options ...]
```

After build you can run test in `build` folder via:
```shell
$ make test
```
