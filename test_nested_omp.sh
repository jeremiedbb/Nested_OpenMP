#!/bin/bash

rm inner.o libinner.so outer &>/dev/null

source /home/jeremie/intel/compilers_and_libraries/linux/bin/compilervars.sh intel64

compilo_outer="gcc"
compilo_inner="icc"

$compilo_inner -Wall -Werror -fPIC -c -fopenmp -O3 -g inner.c
$compilo_inner -shared -fopenmp -o libinner.so inner.o

$compilo_outer -L. -Wl,-rpath=. -Wall -fopenmp -O3 -g -o outer outer.c -linner

./outer
