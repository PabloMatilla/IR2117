all: utils.o median mode

utils.o: utils.cpp
	g++ -I$(HOME)/Documents/eigen3.4 -c utils.cpp

median: median.cpp
	g++ -I$(HOME)/Documents/eigen3.4 -o median median.cpp utils.o

mode: mode.cpp
	g++ -I$(HOME)/Documents/eigen3.4 -o mode mode.cpp utils.o
