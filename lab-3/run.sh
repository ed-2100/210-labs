#!/bin/bash
set -e

cd $(dirname "$0")
g++ ./main.cpp -o a.out
cat ./test_hardees.txt | ./a.out
