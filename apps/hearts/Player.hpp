#ifndef HEARTS_PLAYER_HPP
#define HEARTS_PLAYER_HPP

#include <Card.hpp>

class Player
{
	public:
		Player(): is_human_(true) {}
		bool			card_in_hand(Card & c)
		{
			for(Card & card : hand_)
				if(card == c) return true;
			return false;
		}
		bool			has_suit(unsigned char s)
		{
			for(Card & card : hand_)
				if(card.suit_ == s) return true;
			return false;
		}
		bool			only_has_suit(unsigned char s)
		{
			for(Card & card : hand_)
				if(card.suit_ != s) return false;
			return true;
		}
		bool			is_human_;
		std::vector<Card>	hand_;
		std::vector<Card>	pile_;
};

#endif
