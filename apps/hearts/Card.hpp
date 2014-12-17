#ifndef HEARTS_CARD_HPP
#define HEARTS_CARD_HPP

class Card
{
	public:
		Card(unsigned char s, unsigned char v): suit_(s), value_(v) {}
		unsigned char	suit_;
		unsigned char	value_;
};

#endif
