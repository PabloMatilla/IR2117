all: prueba median mode

prueba: prueba.cpp utils.o
    g++ -I/usr/include/eigen3 -o prueba prueba.cpp utils.ccp

median: median.cpp utils.o
    g++ -I/usr/include/eigen3 -o median median.cpp utils.o

mode: mode.ccp utils.o
    g++ -I/usr/include/eigen3 -o mode mode.cpp utils.o

utils.o: utils.ccp utils.hpp
    g++ -I/usr/include/eigen3 -c utils.ccp
