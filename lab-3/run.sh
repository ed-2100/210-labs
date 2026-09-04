#!/bin/bash
set -e

cd $(dirname "$0")
g++ ./main.cpp -o main
cat ./test_hardees.txt | ./main
