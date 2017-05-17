#include <string.h>
#include <assert.h>
#include <algorithm>

#include <Deck.hpp>
#include <Player.hpp>

Player::Player(char * name):
	cum_score_(0)
{
	strcpy(name_, name);
}

std::vector<Player::S_C>	Player::legal_plays(Deck & deck, bool is_lead)
{
	std::vector<Player::S_C> cards;

	for(auto c : hand_) {
	
		if(is_lead) {
			if(c->suit_ == 2)
				if(!deck.hearts_broken_)
					if(!only_has_suit(2))
						continue;
		} else {
			if(has_suit(deck.lead_)) // not void in lead suit
				if(c->suit_ != deck.lead_)
					continue;
		}
		
		cards.push_back(c);
	}

	return cards;
}
void		Player::remove_from_hand(S_C c)
{
	// remove from hand
	auto it = std::find(hand_.begin(), hand_.end(), c);
	hand_.erase(it);
}
void Player::print_hand()
{
	for(auto c : hand_)
		printf("%s\n", c->string());
}
int Player::score()
{
	int s = 0;
	
	for(int i = 0; i < pile_.size(); i++) {
		S_C c = pile_[i];
		if(c->suit_ == 2) s++;
		else if(c->suit_ == 3)
			if(c->value_ == 0xa) s += 13;
	}

	return s;
}

std::vector<Card> Player::cards_of_suit_outside(int suit)
{
	std::vector<Card> ret;

	for(S_C c : cards_outside_)
	{
	}
}

void		Player::give_card(S_C c)
{
	hand_.push_back(c);
	
	auto it = std::find(cards_outside_.begin(), cards_outside_.end(), c);
	
	assert(it != cards_outside_.end());

	cards_outside_.erase(it);
}

void		Player::sort_hand()
{
	std::sort(hand_.begin(), hand_.end(), card_less);
}

unsigned int		Player::cards_in_hand()
{
	return hand_.size();
}

bool			Player::has_card_in_hand(S_C c)
{
	auto it = std::find(hand_.begin(), hand_.end(), c);
	return it != hand_.end();
}
S_C			Player::get_card(Suit s, unsigned char v)
{
	for(auto card : hand_) {
		if(card->suit_ == s) {
			if(card->value_ == v) return card;
		}
	}
	
	throw Player::card_not_in_hand();

	return S_C();
}
void			Player::reset(Deck & deck)
{
	//std::copy(deck.cards_.begin(), deck.cards_.end(), cards_outside_.end());
	cards_outside_ = deck.cards_;
}




