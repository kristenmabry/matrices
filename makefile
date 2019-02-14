a.out: csquarematrix.o main.o csortedlist.o
	g++ -std=c++11 csquarematrix.o main.o csortedlist.o

main.o: main.cpp csquarematrix.h csortedlist.h
	g++ -std=c++11 -c main.cpp

csquarematrix.o: csquarematrix.cpp csquarematrix.h
		g++ -std=c++11 -c csquarematrix.cpp

csortedlist.o: csortedlist.cpp csortedlist.h
		g++ -c csortedlist.cpp
