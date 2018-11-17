FLAGS=-std=c++11

prog: main.o packagemanager.o utils.o
	g++ $(FLAGS) -o sysget.o main.o packagemanager.o utils.o

main.o: main.cpp
	g++ $(FLAGS) -c main.cpp

packagemanager.o: packagemanager.hpp packagemanager.cpp
	g++ $(FLAGS) -c packagemanager.hpp packagemanager.cpp

utils.o: utils.hpp utils.cpp
	g++ $(FLAGS) -c utils.hpp utils.cpp

install:
	cp sysget.o /usr/local/bin/sysget
	cp ../bash/bash-completion.bash /etc/bash_completion.d/sysget

uninstall:
	rm /usr/local/bin/sysget
	rm -rf /etc/sysget
	rm /etc/bash_completion.d/sysget