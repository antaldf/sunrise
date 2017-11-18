CC=gcc
CFLAGS=-Wall -pthread  -lpigpiod_if2 -lrt   -std=gnu99 
LIBS=-lpigpiod_if2 -lrt -lm



%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

all: sunrise green rg

sunrise: sunrise.o
	gcc -o sunrise sunrise.o -I. $(LIBS)
	rm -f on off getc
	ln sunrise on
	ln sunrise off
	ln sunrise getc

rg: rg.o
	gcc -o rg rg.o -I. $(LIBS)

green: green.o
	gcc -o green green.o -I. $(LIBS)

#on: on.o
#	gcc -o on on.o -I. $(LIBS)

#on2: on2.o
#	gcc -o on2 on2.o -I. $(LIBS)

#off: off.o
#	gcc -o off off.o -I. $(LIBS)


install:
	rm /usr/local/bin/on
	rm /usr/local/bin/off
	rm /usr/local/bin/getc
	rm /usr/local/bin/sunrise
	cp sunrise /usr/local/bin
	ln sunrise /usr/local/bin/on
	ln sunrise /usr/local/bin/off
	ln sunrise /usr/local/bin/getc

clean:
	rm *.o
