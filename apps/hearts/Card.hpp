#ifndef HEARTS_CARD_HPP
#define HEARTS_CARD_HPP

class Card
{
	public:
		Card(unsigned char s, unsigned char v): suit_(s), value_(v) {}
		bool operator==(Card const & card) const
		{
			return (suit_ == card.suit_) && (value_ == card.value_);
		}
		bool is_valid()
		{
			if(suit_ > 3) return false;
			if(value_ > 0xc) return false;
			return 1;
		}
		char * string();
		unsigned char	suit_;
		unsigned char	value_;
};

#endif
