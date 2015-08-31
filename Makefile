all: reverse arrays

union: union.cpp
	g++ union.cpp -o union -I./

reverse: reverse.cpp
	g++ reverse.cpp -o reverse -I./

arrays: arrays.cpp
	g++ arrays.cpp -o arrays -I./

three_sum: three_sum.cpp
	g++ three_sum.cpp -o three_sum 
