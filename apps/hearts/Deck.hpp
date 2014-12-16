#ifndef HEARTS_DECK_HPP
#define HEARTS_DECK_HPP

#include <vector>

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
		int		play(int i, int c = -1);

		std::vector<bool>			is_human_;
		std::vector<unsigned char>		cards_;
		std::vector<std::vector<unsigned char>>	hands_;
		std::vector<std::vector<unsigned char>>	piles_;
		std::vector<unsigned char>		trick_;

};

#endif
