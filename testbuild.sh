#!/bin/bash

cd build

# test maincsv
# prints the summary of the statistics measure calculated in a file outputIris
./maincsv ../csv_examples/Iris.csv output


# test mainode
./mainode # saves results of the applications of the methods on a fixed function in a the suitable files printed in the terminal
