all: median mode

median: median.cpp utils.o
   g++ -I$HOME/Documents/eigen3.4 -o median median.cpp utils.o

mode: mode.ccp utils.o
    g++ -I$HOME/Documents/eigen3.4 -o mode mode.cpp utils.o

utils.o: utils.ccp utils.hpp
    g++ -I$HOME/Documents/eigen3.4 -c utils.cpp

