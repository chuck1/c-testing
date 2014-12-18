#include <assert.h>
#include <stdio.h>

#include <algorithm>

#include <Deck.hpp>
#include <Player.hpp>

Computer::Computer(char * name):
	Player(name)
{
}
Card Computer::play(Deck & deck, bool is_lead)
{

	unsigned int tmp_s;
	unsigned int tmp_v;

	if(deck.verbose_) printf("%s:\n", name_);

	Card tmp(0,0);
	
	std::vector<Card> cards = legal_plays(deck, is_lead);

	if(cards.empty()) {
		printf("legal plays is empty\n");
		print_hand();
		abort();
	}
	
	auto c_min = std::min_element(cards.begin(), cards.end(), card_less);

	remove_from_hand(*c_min);

	return *c_min;
}

