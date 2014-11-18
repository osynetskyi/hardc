CFLAGS=-Wall -g

all: game game2

game2: ex19.o object.o

game: ex19.o object.o

ex19.o: object.o

test: 
	./test_script.sh

clean:
	rm -f game
	rm -f game2
	rm -f ex19.o
	rm -f object.o
