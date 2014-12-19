#ifndef HEARTS_DECK_HPP
#define HEARTS_DECK_HPP

#include <vector>

#include <Player.hpp>
#include <Card.hpp>

class Deck
{
	public:
		Deck();
		void		init(int);
		void		deal();
		int		cards_in_hand();
		int		score(int);
		int		high_score();
		int		low_score();
		int		whos_got_the_two();
		int		play(int i, Card * c = 0);

		bool					hearts_broken_;



		std::vector<Player*>			players_;
		std::vector<Card>			cards_;

		// trick data
		int					player_current_;
		int					player_lead_;

		std::vector<Card>			trick_;
		unsigned char				lead_;

		bool					verbose_;
};

#endif
