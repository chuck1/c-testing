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
		bool			has_suit(Suit s)
		{
			for(Card & card : hand_)
				if(card.suit_ == s) return true;
			return false;
		}
		bool			only_has_suit(Suit s)
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
		unsigned int		cards_in_hand();
		void			sort_hand();
		void			give_card(Card c);
		bool			has_card_in_hand(Card c);
		// stats
		std::vector<Card>	cards_of_suit_outside(int suit);

	private:
		std::vector<Card>	cards_outside_;
		std::vector<Card>	hand_;
	public:
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
