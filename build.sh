#!/bin/bash

set -x # print commands executed

# compile csvparser and odesolver as dynamic libraries
cd src
mkdir csvparser
cd csvparser
cmake -DLIB_TO_COMPILE="csvparser" ..
make

cd ..
mkdir odesolver
cd odesolver
cmake -DLIB_TO_COMPILE="odesolver" ..
make


