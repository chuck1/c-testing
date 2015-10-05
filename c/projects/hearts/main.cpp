/*
 * TODO
 * implement passing
 * setup to do combinations of human and computer
 * implement statistics functions
 *    - how many cards of suit left inlother players hands
 *        - that are lower than my lowest
 *    - likelihood of players to left being void in suit
 */

#include <assert.h>
#include <stdio.h>

#include <Deck.hpp>


int		main()
{
	Deck deck;

	deck.verbose_ = false;

	deck.init(3,1);

	// game

	int count = 0;

	while(deck.high_score() < 100) {

		deck.play_hand();

		count++;
	}

	printf("%i hands\n", count);

	for(int i = 0; i < deck.players_.size(); i++) {
		Player & p = *deck.players_[i];
		printf("%2i ", p.cum_score_);
	}
	printf("\n");

	return 0;
}


