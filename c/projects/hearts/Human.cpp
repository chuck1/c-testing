#include <assert.h>
#include <stdio.h>

#include <algorithm>

#include <Deck.hpp>
#include <Player.hpp>

class bad_input_suit {};
class bad_input_card {};

Suit		char_to_suit(char c)
{
	switch(c) {
		case 'c':
			return Suit(0);
		case 'd':
			return Suit(1);
		case 'h':
			return Suit(2);
		case 's':
			return Suit(3);
		default:
			printf("suit char '%c'\n", c);
			throw bad_input_suit();
	}
	return Suit();
}
unsigned char	char_to_card(char c)
{
	switch(c) {
		case '2':
			return 0;
		case '3':
			return 1;
		case '4':
			return 2;
		case '5':
			return 3;
		case '6':
			return 4;
		case '7':
			return 5;
		case '8':
			return 6;
		case '9':
			return 7;
		case '0':
			return 8;
		case 'j':
			return 9;
		case 'q':
			return 10;
		case 'k':
			return 11;
		case 'a':
			return 12;
		default:
			printf("card char '%c'\n", c);
			throw bad_input_card();
	}
	return 0;
}

Human::Human(char * name):
	Player(name)
{
}
S_C		Human::play(Deck & deck, bool is_lead)
{

	char tmp_s;
	char tmp_v;

	printf("%s:\n", name_);

	S_C card;
	
	auto cards = legal_plays(deck, is_lead);

	if(0) {	
	for(auto c : cards) {
		printf("  %s\n", c->string());
	}
	}

	assert(!cards.empty());

	while(1) {
		scanf("%s %s", &tmp_s, &tmp_v);
	
		Suit s;
		unsigned char c;

		try {
			s = char_to_suit(tmp_s);
		} catch(...) {
			continue;
		}

		try {
			c = char_to_card(tmp_v);
		} catch(...) {
			continue;
		}
		
		/*
		if(!tmp->is_valid()) {
			printf("invalid card\n");
			fflush(stdout);
			continue;
		}
		*/


		try {
			card = get_card(s, c);
		} catch(Player::card_not_in_hand & e) {
			printf("you dont have that card\n");
			continue;
		}

		auto it = std::find(cards.begin(), cards.end(), card);
		
		if(it == cards.end()) {
			printf("not a legal move\n");
			fflush(stdout);
			continue;
		}

		break;
	}

	remove_from_hand(card);

	return card;
}

