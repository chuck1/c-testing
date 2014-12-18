#include <assert.h>
#include <stdio.h>

#include <algorithm>

#include <Deck.hpp>
#include <Player.hpp>

Human::Human(char * name):
	Player(name)
{
}
Card Human::play(Deck & deck, bool is_lead)
{

	unsigned int tmp_s;
	unsigned int tmp_v;

	printf("%s:\n", name_);

	Card tmp(0,0);
	
	auto cards = legal_plays(deck, is_lead);
	assert(!cards.empty());

	while(1) {
		scanf("%x %x", &tmp_s, &tmp_v);

		tmp.suit_ = tmp_s;
		tmp.value_ = tmp_v;

		if(!tmp.is_valid()) {
			printf("invalid card\n");
			fflush(stdout);
			continue;
		}

		auto it = std::find(cards.begin(), cards.end(), tmp);
		
		if(it == cards.end()) {
			printf("not a legal move\n");
			fflush(stdout);
			continue;
		}

		break;
	}
	return tmp;
}

