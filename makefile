FLAGS=-std=c++11 -Wall -Wextra -Wpedantic
INSTALLDEST=/usr/local/bin/sysget
CCP=g++

prog: main.o packagemanager.o utils.o translation.o
	$(CCP) $(FLAGS) -o sysget main.o packagemanager.o utils.o translation.o

main.o: src/main.cpp src/main.hpp
	$(CCP) $(FLAGS) -c src/main.cpp src/main.hpp

packagemanager.o: src/packagemanager.hpp src/packagemanager.cpp
	$(CCP) $(FLAGS) -c src/packagemanager.hpp src/packagemanager.cpp

utils.o: src/utils.hpp src/utils.cpp
	$(CCP) $(FLAGS) -c src/utils.hpp src/utils.cpp

translation.o: src/translation.hpp src/translation.cpp
	$(CCP) $(FLAGS) -c src/translation.hpp src/translation.cpp

install:
	cp sysget $(INSTALLDEST)
	mkdir -p /usr/local/man/man8
	cp contrib/man/sysget.8 /usr/local/man/man8/sysget.8
	gzip /usr/local/man/man8/sysget.8
	cp contrib/sysget.bash-completion /etc/bash_completion.d/sysget

uninstall:
	rm -rf /usr/local/bin/sysget
	rm -rf /etc/sysget/
	rm -rf /etc/bash_completion.d/sysget
	rm -rf /usr/local/man/man8/sysget.8.gz

clean:
	rm -rf *.o src/*.gch
	rm -rf *.o src/libs/*.gch
	rm -rf sysget
