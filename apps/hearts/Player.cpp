#include <string.h>

#include <algorithm>

#include <Deck.hpp>
#include <Player.hpp>

Player::Player(char * name):
	cum_score_(0)
{
	strcpy(name_, name);
}

std::vector<Card> Player::legal_plays(Deck & deck, bool is_lead)
{
	std::vector<Card> cards;

	for(Card & c : hand_) {
	
		if(is_lead) {
			if(c.suit_ == 2)
				if(!deck.hearts_broken_)
					if(!only_has_suit(2))
						continue;
		} else {
			if(has_suit(deck.lead_)) // not void in lead suit
				if(c.suit_ != deck.lead_)
					continue;
		}
		
		cards.push_back(c);
	}

	return cards;
}
void Player::remove_from_hand(Card & c)
{
	// remove from hand
	auto it = std::find(hand_.begin(), hand_.end(), c);
	hand_.erase(it);
}
void Player::print_hand()
{
	for(Card & c : hand_)
		printf("%s\n", c.string());
}
int Player::score()
{
	int s = 0;
	
	for(int i = 0; i < pile_.size(); i++) {
		Card c = pile_[i];
		if(c.suit_ == 2) s++;
		else if(c.suit_ == 3)
			if(c.value_ == 0xa) s += 13;
	}

	return s;
}

