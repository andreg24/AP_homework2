#!/bin/bash

set -x # print commands executed

# compile csvparer as shared library
cd src
mkdir csvparser
cd csvparser
cmake -D
make

# compile odesolver as shared library
cd ..
mkdir odesolver
cd odesolver
cmake -DLIB_TO_COMPILE="odesolver" ..
make

# compile main

