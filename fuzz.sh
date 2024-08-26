#!/bin/bash
n=${1:-10}
p=${2:-4}
echo "Running $n Random tests with a max of $p concurrent processes"
build/fuzzTest $n $p
