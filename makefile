FLAGS=-std=c++11

prog:
	g++ $(FLAGS) -o sysget.o src/*.hpp src/*.cpp

install:
	cp sysget.o /usr/local/bin/sysget
	cp bash/bash-completion.bash /etc/bash_completion.d/sysget

uninstall:
	rm /usr/local/bin/sysget
	rm -rf /etc/sysget
	rm /etc/bash_completion.d/sysget