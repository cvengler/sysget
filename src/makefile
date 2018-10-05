prog: main.o search.o utils.o install.o remove.o update.o clean.o
	g++ -o sysget.o main.o search.o utils.o install.o remove.o update.o clean.o

main.o: main.cpp
	g++ -c main.cpp

utils.o: utils.h utils.cpp
	g++ -c utils.h utils.cpp

search.o: search.h search.cpp
	g++ -c search.h search.cpp
	
install.o: install.h install.cpp
	g++ -c install.h install.cpp

remove.o: remove.h remove.cpp
	g++ -c remove.h remove.cpp

update.o: update.h update.cpp
	g++ -c update.h update.cpp

clean.o: clean.h clean.cpp
	g++ -c clean.h clean.cpp
