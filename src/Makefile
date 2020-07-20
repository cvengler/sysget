CFLAGS=-std=c89 -Wall -Wextra -Wpedantic

all: main.o
	$(CC) $(CFLAGS) -o sysget main.o $(LDFLAGS)

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

clean:
	$(RM) sysget
	$(RM) *.o
	$(RM) *.gch
