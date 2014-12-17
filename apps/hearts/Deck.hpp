#ifndef HEARTS_DECK_HPP
#define HEARTS_DECK_HPP

#include <vector>

#include <Player.hpp>
#include <Card.hpp>

class Deck
{
	public:
		Deck();
		void		deal(int);
		int		cards_in_hand();
		int		score(int);
		int		high_score();
		int		low_score();
		int		whos_got_the_two();
		int		play(int i, Card * c = 0);
		Card		stdin_card(char * msg, Player & p, unsigned char * lead);

		bool					hearts_broken_;
		std::vector<Player>			players_;
		std::vector<Card>			cards_;
		std::vector<Card>			trick_;

};

#endif
