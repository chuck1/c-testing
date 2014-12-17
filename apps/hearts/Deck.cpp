
#include <random>
#include <algorithm>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <Deck.hpp>

Deck::Deck()
{

	for(unsigned char suit = 0; suit < 4; suit++) {
		for(unsigned char i = 0; i < 13; i++) {
			cards_.push_back(Card(suit, + i));
		}
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(cards_.begin(), cards_.end(), g);
}

bool card_less(Card const & c0, Card const & c1)
{
	if(c0.suit_ == c1.suit_) return c0.value_ < c1.value_;
	return c0.suit_ < c1.suit_;
}

void Deck::deal(int hands)
{
	int cards_per_hand = 52 / hands;

	int extra = 52 % hands;
	

	players_.clear();
	players_.resize(hands);

	int k = 0;
	for(int i = 0; i < cards_per_hand; i++) {
		for(int j = 0; j < hands; j++) {
			Card c = cards_[k++];
			players_[j].hand_.push_back(c);
			
			printf("%X %X    ", c.suit_, c.value_);
		}
		printf("\n");
	}

	for(int j = 0; j < hands; j++)
		std::sort(players_[j].hand_.begin(), players_[j].hand_.end(), card_less);

	for(int i = 0; i < cards_per_hand; i++) {
		for(int j = 0; j < hands; j++) {
			Card c = players_[j].hand_[i];
			printf("%X %X    ", c.suit_, c.value_);
		}
		printf("\n");
	}

}

int Deck::cards_in_hand()
{
	if(players_.empty()) return 0;
	return players_[0].hand_.size();
}

int Deck::score(int p)
{
	assert(p < players_.size());
	
	int s = 0;
	
	std::vector<Card> & pile = players_[p].pile_;

	for(int i = 0; i < pile.size(); i++) {
		Card c = pile[i];
		if(c.suit_ == 2) s++;
		else if(c.suit_ == 3)
			if(c.value_ == 0xa) s += 13;
	}

	return s;
}

int Deck::high_score()
{
	int hs = 0;
	
	for(int i = 0; i < players_.size(); i++) {
		int s = score(i);
		if(s > hs) hs = s;
	}

	return hs;
}


int Deck::whos_got_the_two()
{
	for(int i = 0; i < players_.size(); i++) {
		for(int j = 0; j < players_[i].hand_.size(); j++) {
			Card & c = players_[i].hand_[j];
			if((c.suit_ == 0) && (c.value_ == 0)) return i;
		}
	}

	return -1;
}

int is_valid(unsigned char c)
{
	if((c >> 4) > 3) return 0;
	if((c & 0xf) > 0xc) return 0;
	return 1;
}
char * suit_string(unsigned char card)
{
	char * buffer = new char[32];
	
	switch(card >> 4) {
		case 0x0:
			strcpy(buffer, "clubs");
			break;
		case 0x1:
			strcpy(buffer, "diamonds");
			break;
		case 0x2:
			strcpy(buffer, "hearts");
			break;
		case 0x3:
			strcpy(buffer, "spades");
			break;
		default:
			printf("invalid suit %x\n", card >> 4);
			abort();
	}

	return buffer;
}

char * card_string(unsigned char c)
{
	char * buffer = new char[128];

	switch(c & 0xf) {
		case 0x0:
			strcpy(buffer, "two");
			break;
		case 0x1:
			strcpy(buffer, "three");
			break;
		case 0x2:
			strcpy(buffer, "four");
			break;
		case 0x3:
			strcpy(buffer, "five");
			break;
		case 0x4:
			strcpy(buffer, "six");
			break;
		case 0x5:
			strcpy(buffer, "seven");
			break;
		case 0x6:
			strcpy(buffer, "eight");
			break;
		case 0x7:
			strcpy(buffer, "nine");
			break;
		case 0x8:
			strcpy(buffer, "ten");
			break;
		case 0x9:
			strcpy(buffer, "jack");
			break;
		case 0xa:
			strcpy(buffer, "queen");
			break;
		case 0xb:
			strcpy(buffer, "king");
			break;
		case 0xc:
			strcpy(buffer, "ace");
			break;
		default:
			printf("invalid card %x\n", c);
			abort();
	}

	strcat(buffer, " of ");

	switch(c >> 4) {
		case 0x0:
			strcat(buffer, "clubs");
			break;
		case 0x1:
			strcat(buffer, "diamonds");
			break;
		case 0x2:
			strcat(buffer, "hearts");
			break;
		case 0x3:
			strcat(buffer, "spades");
			break;
		default:
			printf("invalid card %x\n", c);
			abort();
	}

	return buffer;
}



int Deck::play(int i, Card * first_card)
{
	unsigned char lead;
	int players = players_.size();
	int h = i;
	//Card & c;

	printf("\n");

	trick_.clear();
	
	if(first_card) {
		// play
		trick_.push_back(*first_card);
		lead = first_card->suit_;
		h = (h+1) % players;
	} else {
		// play a card
		if(players_[h].is_human_) {
			unsigned int tmp;
			printf("player %i:\n", h);
			scanf("%x", &tmp);
			if(!is_valid(tmp)) abort();
			printf("player %i leads with the %s\n", h, card_string(tmp));
			
			// play
			trick_.push_back(Card(tmp >> 4, tmp & 0xf));
			lead = tmp >> 4;
			h = (h+1) % players;

		} else {
			printf("not impl\n");
			abort();			
		}
	}

	printf("%s are lead\n", suit_string(lead << 4));

	// loop back to i
	while(h != i) {	
		// play a card
		if(players_[h].is_human_) {
			unsigned int tmp;
			printf("player %i:\n", h);
			scanf("%x", &tmp);
			if(!is_valid(tmp)) abort();
			printf("player %i played the %s\n", h, card_string(tmp));

			// play
			trick_.push_back(Card(tmp >> 4, tmp & 0xf));
			h = (h+1) % players;

		} else {
			printf("not impl\n");
			abort();			
		}
	}
	
	unsigned char high_trump = 0;
	int winner;
	
	for(int j = 0; j < players; j++) {
		// player index
		int k = (j + i) % players;

		Card c = trick_[j];
		
		if(c.suit_ != lead) continue;
		
		if(c.value_ > high_trump) {
			high_trump = c.value_;
			winner = k;
		}
	}
	
	printf("player %i takes the trick with the %s\n", winner, card_string((lead << 4) + high_trump));

	return winner;
}






