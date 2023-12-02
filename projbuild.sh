#!/bin/bash

set -x # print commands executed

BOOST_ROOT=$1 # example: ~/Desktop/uni/advanced_programming/homeworks/extlib
EIGEN_PATH=$2 # example: /usr/local/include/eigen3

# execute cmake command
rm -r build
mkdir build
cd build
cmake -DBOOST_ROOT=${BOOST_ROOT} -DEIGEN_PATH=${EIGEN_PATH} ..
make
cd ..
