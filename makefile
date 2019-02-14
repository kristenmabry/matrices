a.out: csquarematrix.o main.o
	g++ -std=c++11 csquarematrix.o main.o

main.o: main.cpp csquarematrix.h
	g++ -std=c++11 -c main.cpp

csquarematrix.o: csquarematrix.cpp csquarematrix.h
		g++ -std=c++11 -c csquarematrix.cpp
