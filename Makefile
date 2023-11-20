# Makefile

CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wpedantic

main: main.cpp csvparser.hpp csvparser.cpp
	$(CXX) csvparser.cpp main.cpp $(CXXFLAGS) -o main
