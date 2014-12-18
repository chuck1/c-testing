CFLAGS = -I. -std=c++0x

all:
	g++ -c main.cpp -o main.o $(CFLAGS)
	g++ -c Deck.cpp -o Deck.o $(CFLAGS)
	g++ -c Card.cpp -o Card.o $(CFLAGS)
	g++ main.o Deck.o Card.o -o hearts $(CFLAGS)

