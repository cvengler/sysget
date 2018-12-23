FLAGS=-std=c++11

prog: src/main.cpp
	g++ $(FLAGS) -o syg src/main.cpp

install:
	cp syg /usr/local/bin/syg

uninstall:
	rm -rf syg /usr/local/bin/syg

clean:
	rm -rf *.o src/*.gch
	rm -rf syg