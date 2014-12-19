#ifndef HEARTS_CARD_HPP
#define HEARTS_CARD_HPP

#include <Suit.hpp>

class Card
{
	public:
		Card(Suit s, unsigned char v): suit_(s), value_(v) {}
		bool operator==(Card const & card) const
		{
			return (suit_ == card.suit_) && (value_ == card.value_);
		}
		bool is_valid()
		{
			if(suit_ > Suit(3)) return false;
			if(value_ > 0xc) return false;
			return 1;
		}
		char * string();
		Suit		suit_;
		unsigned char	value_;
};

inline bool card_less(Card const & c0, Card const & c1)
{
	if(c0.suit_ == c1.suit_) return c0.value_ < c1.value_;
	return c0.suit_ < c1.suit_;
}


#endif
