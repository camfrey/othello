CC=g++
CFLAGS=-I.
DEPS = game.h

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

make: main.o functions.o
	$(CC) -o othello main.o functions.o

clean:
	rm othello
	rm -f ./*.o
