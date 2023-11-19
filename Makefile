# Makefile

CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wpedantic

$@: $@.cpp
	$(CXX) $@.cpp $(CXXFLAGS) -o $@
