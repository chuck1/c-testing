#include <stdio.h>

#include <Deck.hpp>

int main()
{
	Deck deck;
	
	deck.deal(4);

	int i = deck.whos_got_the_two();
	if(i < 0) return i;
	
	printf("%i has the two\n", i);
	
	// play the two
	i = deck.play(i, 0x00);

	while(deck.high_score() < 100) {
		while(deck.cards_in_hand() > 0) {
			i = deck.play(i);
		}
	}
	
	return 0;
}


