#ifndef HEARTS_PLAYER_HPP
#define HEARTS_PLAYER_HPP

#include <vector>

#include <Card.hpp>

class Deck;

class Player
{
	public:
		Player(char * name);
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
		void			remove_from_hand(Card & c);
		void			print_hand();
		virtual Card		play(Deck & deck, bool is_lead) = 0;
		std::vector<Card>	legal_plays(Deck & deck, bool is_lead);
		int			score();
		std::vector<Card>	hand_;
		std::vector<Card>	pile_;
		char			name_[32];
		int			cum_score_;
};

class Human: public Player
{
	public:
		Human(char * name);
		virtual Card		play(Deck & deck, bool is_lead);
};

class Computer: public Player
{
	public:
		Computer(char * name);
		virtual Card		play(Deck & deck, bool is_lead);
};

#endif
