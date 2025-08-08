CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g
OBJ = programm.o person_manager.o

all: programm

programm: $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ)

programm.o: programm.c person_manager.h
person_manager.o: person_manager.c person_manager.h person.h

clean:
	rm -f *.o programm
