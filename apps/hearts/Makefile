CFLAGS = -I. -std=c++0x -g

all:
	g++ -c main.cpp -o main.o $(CFLAGS)
	g++ -c Deck.cpp -o Deck.o $(CFLAGS)
	g++ -c Card.cpp -o Card.o $(CFLAGS)
	g++ -c Player.cpp -o Player.o $(CFLAGS)
	g++ -c Human.cpp -o Human.o $(CFLAGS)
	g++ -c Computer.cpp -o Computer.o $(CFLAGS)
	g++ main.o Deck.o Card.o Player.o Human.o Computer.o -o hearts $(CFLAGS)

