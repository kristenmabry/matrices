a.out: csquarematrix.o main.o clist.o
	g++ -std=c++11 csquarematrix.o main.o clist.o

main.o: main.cpp csquarematrix.h clist.h
	g++ -std=c++11 -c main.cpp

csquarematrix.o: csquarematrix.cpp csquarematrix.h
		g++ -std=c++11 -c csquarematrix.cpp

clist.o: clist.cpp clist.h csquarematrix.h
	 g++ -std=c++11 -c clist.cpp
