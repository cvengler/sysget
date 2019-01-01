FLAGS=-std=c++11

prog: main.o packagemanager.o utils.o
	g++ $(FLAGS) -o sysget main.o packagemanager.o utils.o

main.o: src/main.cpp
	g++ $(FLAGS) -c src/main.cpp

packagemanager.o: src/packagemanager.hpp src/packagemanager.cpp
	g++ $(FLAGS) -c src/packagemanager.hpp src/packagemanager.cpp

utils.o: src/utils.hpp src/utils.cpp
	g++ $(FLAGS) -c src/utils.hpp src/utils.cpp

install:
	cp sysget /usr/local/bin/sysget
	cp contrib/man/sysget.1 /usr/local/man/man8/sysget.1
	gzip /usr/local/man/man8/sysget.1
	cp contrib/sysget.bash-completion /etc/bash_completion.d/sysget
	
maninstall:
	cp contrib/man/sysget.1 /usr/local/man/man8/sysget.1
	gzip /usr/local/man/man8/sysget.1

uninstall:
	rm -rf /usr/local/bin/sysget
	rm -rf /etc/sysget
	rm -rf /etc/bash_completion.d/sysget
	rm -rf /etc/sysget_config
	rm -rf /etc/sysget_custom
	rm -rf /etc/sysget_args

clean:
	rm -rf *.o src/*.gch
	rm -rf sysget
