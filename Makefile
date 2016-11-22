CC=gcc
CFLAGS=-Wall -pthread  -lpigpiod_if2 -lrt
LIBS=-lpigpiod_if2 -lrt -lm



%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: sunrise on off

sunrise: sunrise.o
	gcc -o sunrise sunrise.o -I. $(LIBS)

on: on.o
	gcc -o on on.o -I. $(LIBS)

off: off.o
	gcc -o off off.o -I. $(LIBS)



clean:
	rm *.o
