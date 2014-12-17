/*
 * TODO
 * create player function that considers the lead suit and hearts_broken and generates list of legal cards to play
 *
 */

#include <stdio.h>

#include <Deck.hpp>

int main()
{
	Deck deck;

	// game

	while(deck.high_score() < 100) {

		// hand

		deck.deal(4);

		int i = deck.whos_got_the_two();
		if(i < 0) return i;

		printf("%i has the two\n", i);

		Card c(0,0);

		// play the two
		i = deck.play(i, &c);

		while(deck.cards_in_hand() > 0) {
			i = deck.play(i);
		}
	}

	return 0;
}


