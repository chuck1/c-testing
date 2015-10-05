#ifndef HEARTS_PLAYER_HPP
#define HEARTS_PLAYER_HPP

#include <vector>

#include <Card.hpp>

class Deck;

class Player
{
	public:

		typedef std::shared_ptr<Card> S_C;

		class card_not_in_hand {};

		Player(char * name);
		bool			card_in_hand(S_C c)
		{
			for(auto card : hand_)
				if(card == c) return true;
			return false;
		}
		bool			has_suit(Suit s)
		{
			for(auto card : hand_)
				if(card->suit_ == s) return true;
			return false;
		}
		bool			only_has_suit(Suit s)
		{
			for(auto card : hand_)
				if(card->suit_ != s) return false;
			return true;
		}
		S_C			get_card(Suit s, unsigned char v);
		void			remove_from_hand(S_C c);
		void			print_hand();
		virtual S_C		play(Deck & deck, bool is_lead) = 0;
		std::vector<S_C>	legal_plays(Deck & deck, bool is_lead);
		int			score();
		unsigned int		cards_in_hand();
		void			sort_hand();
		void			give_card(S_C c);
		bool			has_card_in_hand(S_C c);
		/**
		 * repopulate cards_outside
		 */
		void			reset(Deck & deck);
		// stats
		std::vector<Card>	cards_of_suit_outside(int suit);

	private:
		std::vector<S_C>	cards_outside_;
		std::vector<S_C>	hand_;
	public:
		std::vector<S_C>	pile_;
		char			name_[32];
		int			cum_score_;
};

class Human: public Player
{
	public:
		Human(char * name);
		virtual S_C		play(Deck & deck, bool is_lead);
};

class Computer: public Player
{
	public:
		Computer(char * name);
		virtual S_C		play(Deck & deck, bool is_lead);
};

#endif
