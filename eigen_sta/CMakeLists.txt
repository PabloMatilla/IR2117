all: prueba prueba.o

utils.o: utils.ccp utils.hpp
    g++ -I/usr/include/eigen3 -c utils.cpp

prueba: prueba.o utils.o
    g++ -I/usr/include/eigen3 -o prueba prueba.o utils.o

prueba.o: prueba.cpp utils.o
    g++ -I/usr/include/eigen3  -c prueba.cpp

