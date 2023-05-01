all: arith_mean median mode

arith_mean: arith_mean.cpp utils.o
    g++ -o arith_mean arith_mean.cpp utils.o

median: median.cpp utils.o
    g++ -o median median.cpp utils.o

mode: mode.ccp utils.o
    g++ -o mode mode.cpp utils.o

utils.o: utils.cc utils.hpp
    g++ -c utils.cc
