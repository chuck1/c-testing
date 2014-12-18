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

int main()
{
	Deck deck;

	deck.verbose_ = false;

	deck.init(4);

	

	// game

	int count = 0;

	while(deck.high_score() < 100) {

		for(int i = 0; i < deck.players_.size(); i++) {
			Player & p = *deck.players_[i];
			printf("%2i ", p.cum_score_);
		}
		printf("\n");

		// hand

		deck.deal();

		int i = deck.whos_got_the_two();
		if(i < 0) return i;
		
		if(deck.verbose_) printf("%i has the two\n", i);
		
		Card c(0,0);

		// play the two
		i = deck.play(i, &c);

		while(deck.cards_in_hand() > 0) {
			i = deck.play(i);
		}

		int tmp = 0;
		int tmp_score = 0;
		// save the scores
		for(int i = 0; i < deck.players_.size(); i++) {
			Player & p = *deck.players_[i];
			
			p.cum_score_ += p.score();
			tmp_score += p.score();

			tmp += p.pile_.size();
			p.pile_.clear();
		}

		assert(tmp_score == 26);
		assert(tmp == 52);

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


