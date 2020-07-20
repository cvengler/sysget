CFLAGS=-std=c89 -Wall -Wextra -Wpedantic

all: main.o packagemanager.o
	$(CC) $(CFLAGS) -o sysget main.o packagemanager.o $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

packagemanager.o: packagemanager.h packagemanager.c
	$(CC) $(CFLAGS) -c packagemanager.h packagemanager.c

clean:
	$(RM) sysget
	$(RM) *.o
	$(RM) *.gch
