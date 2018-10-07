FLAGS=-std=c++11

prog: main.o search.o utils.o install.o remove.o update.o clean.o
	g++ $(FLAGS) -o sysget.o main.o search.o utils.o install.o remove.o update.o clean.o

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

utils.o: utils.h utils.cpp
	g++ $(FLAGS) -c utils.h utils.cpp

search.o: search.h search.cpp
	g++ $(FLAGS) -c search.h search.cpp
	
install.o: install.h install.cpp
	g++ $(FLAGS) -c install.h install.cpp

remove.o: remove.h remove.cpp
	g++ $(FLAGS) -c remove.h remove.cpp

update.o: update.h update.cpp
	g++ $(FLAGS) -c update.h update.cpp

clean.o: clean.h clean.cpp
	g++ $(FLAGS) -c clean.h clean.cpp
