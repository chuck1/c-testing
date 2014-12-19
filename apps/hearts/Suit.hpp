#ifndef SUIT_HPP
#define SUIT_HPP

class Suit
{
	public:
		friend bool suit_less(Suit const & s0, Suit const & s1);
		Suit(): suit_(0) {}
		Suit(unsigned char s): suit_(s)
		{

		}
		char *			string();
		bool			operator==(Suit const & s) const
		{
			return suit_ == s.suit_;
		}
		bool			operator!=(Suit const & s) const
		{
			return suit_ != s.suit_;
		}
		bool			operator<(Suit const & s) const 
		{
			return suit_ < s.suit_;
		}
		bool			operator>(Suit const & s) const 
		{
			return suit_ > s.suit_;
		}
	private:
		unsigned char		suit_;
};

inline bool suit_less(Suit const & s0, Suit const & s1)
{
	return s0.suit_ < s1.suit_;
}

#endif
