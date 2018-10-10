FLAGS=-std=c++11

prog: main.o search.o utils.o install.o remove.o update.o clean.o
	g++ $(FLAGS) -o sysget.o main.o search.o utils.o install.o remove.o update.o clean.o

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

utils.o: utils.hpp utils.cpp
	g++ $(FLAGS) -c utils.hpp utils.cpp

search.o: search.hpp search.cpp
	g++ $(FLAGS) -c search.hpp search.cpp
	
install.o: install.hpp install.cpp
	g++ $(FLAGS) -c install.hpp install.cpp

remove.o: remove.hpp remove.cpp
	g++ $(FLAGS) -c remove.hpp remove.cpp

update.o: update.hpp update.cpp
	g++ $(FLAGS) -c update.hpp update.cpp

clean.o: clean.hpp clean.cpp
	g++ $(FLAGS) -c clean.hpp clean.cpp

install:
	cp sysget.o /usr/local/bin/sysget 

uninstall:
	rm /usr/local/bin/sysget
	rm -rf /usr/local/share/sysget