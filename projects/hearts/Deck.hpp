#ifndef HEARTS_DECK_HPP
#define HEARTS_DECK_HPP

#include <vector>
#include <memory>

#include <Player.hpp>
#include <Card.hpp>
#include <Suit.hpp>

class Deck
{
	public:
		typedef std::shared_ptr<Card> S_C;

		Deck();
		void		init(int, int);
		void		deal();
		int		score(int);
		int		cards_in_hand();
		int		high_score();
		int		low_score();
		int		whos_got_the_two();
		/** play a trick
		 *
		 * player i leads
		 * return the player who takes the trick
		 */
		int		play(int i, S_C c = 0);
		
		void		play_hand();

		bool					hearts_broken_;

		S_C		find_card(Suit s, unsigned char c);

		std::vector<Player*>			players_;
		std::vector<S_C>			cards_;

		// trick data
		int					player_current_;
		int					player_lead_;

		std::vector<S_C>			trick_;
		Suit					lead_;

		bool					verbose_;
};

#endif
