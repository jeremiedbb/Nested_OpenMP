#!/bin/bash

rm inner.o libinner.so outer &>/dev/null

source /home/jeremie/intel/compilers_and_libraries/linux/bin/compilervars.sh intel64

compilo_outer="gcc"
compilo_inner="icc"

# use -qopenmp if icc or -fopenmp if clang/gcc
$compilo_inner -Wall -Werror -fPIC -c -qopenmp -O3 -g inner.c
$compilo_inner -shared -qopenmp -o libinner.so inner.o

$compilo_outer -L. -Wl,-rpath=. -Wall -fopenmp -O3 -g -o outer outer.c -linner

./outer
