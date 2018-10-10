FLAGS=-std=c++11

prog: main.o search.o utils.o install.o remove.o update.o clean.o
	g++ $(FLAGS) -o sysget.o main.o search.o utils.o install.o remove.o update.o clean.o

main.o: src/main.cpp
	g++ $(FLAGS) -c src/main.cpp

utils.o: src/utils.cpp
	g++ $(FLAGS) -c src/utils.cpp

search.o: src/search.cpp
	g++ $(FLAGS) -c src/search.cpp
	
install.o: src/install.cpp
	g++ $(FLAGS) -c src/install.cpp

remove.o: src/remove.cpp
	g++ $(FLAGS) -c src/remove.cpp

update.o: src/update.cpp
	g++ $(FLAGS) -c src/update.cpp

clean.o: src/clean.cpp
	g++ $(FLAGS) -c src/clean.cpp

install:
	cp sysget.o /usr/local/bin/sysget 

uninstall:
	rm /usr/local/bin/sysget
	rm -rf /usr/local/share/sysget