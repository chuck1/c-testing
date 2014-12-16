
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
			cards_.push_back((suit << 4) + i);
		}
	}

	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(cards_.begin(), cards_.end(), g);

	for(auto card : cards_) printf("%X %X\n", card >> 4, card & 0xf);
}

void Deck::deal(int hands)
{
	int cards_per_hand = 52 / hands;

	int extra = 52 % hands;
	
	hands_.clear();
	hands_.resize(hands);

	piles_.clear();
	piles_.resize(hands);
	
	is_human_.resize(hands, true);

	int k = 0;
	for(int i = 0; i < cards_per_hand; i++) {
		for(int j = 0; j < hands; j++) {
			unsigned char c = cards_[k++];
			hands_[j].push_back(c);
			
			printf("%X %X    ", c >> 4, c & 0xf);
		}
		printf("\n");
	}

	for(int j = 0; j < hands; j++)
		std::sort(hands_[j].begin(), hands_[j].end());

	for(int i = 0; i < cards_per_hand; i++) {
		for(int j = 0; j < hands; j++) {
			unsigned char c = hands_[j][i];
			printf("%X %X    ", c >> 4, c & 0xf);
		}
		printf("\n");
	}

}

int Deck::cards_in_hand()
{
	if(hands_.empty()) return 0;
	return hands_[0].size();
}

int Deck::score(int p)
{
	assert(p < piles_.size());
	
	int s = 0;
	
	std::vector<unsigned char> & pile = piles_[p];

	for(int i = 0; i < pile.size(); i++) {
		unsigned char & c = pile[i];
		if((c >> 4) == 2) s++;
		else if((c >> 4) == 3)
			if((c & 0xf) == 0xa) s += 13;
	}

	return s;
}

int Deck::high_score()
{
	int hs = 0;
	
	for(int i = 0; i < piles_.size(); i++) {
		int s = score(i);
		if(s > hs) hs = s;
	}

	return hs;
}


int Deck::whos_got_the_two()
{
	for(int i = 0; i < hands_.size(); i++) {
		for(int j = 0; j < hands_[i].size(); j++) {
			if(hands_[i][j] == 0) return i;
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



int Deck::play(int i, int first_card)
{
	unsigned char lead;
	int hands = hands_.size();
	int h = i;
	unsigned char c;

	printf("\n");

	trick_.clear();
	
	if(first_card > -1) {
		// play
		trick_.push_back(c);
		lead = first_card >> 4;
		h = (h+1) % hands;
	} else {
		// play a card
		if(is_human_[h]) {
			unsigned int tmp;
			printf("player %i:\n", h);
			scanf("%x", &tmp);
			c = tmp;
			if(!is_valid(c)) abort();
			printf("player %i leads with the %s\n", h, card_string(c));
			
			// play
			trick_.push_back(c);
			lead = c >> 4;
			h = (h+1) % hands;

		} else {
			printf("not impl\n");
			abort();			
		}
	}

	printf("%s are lead\n", suit_string(lead << 4));

	// loop back to i
	while(h != i) {	
		// play a card
		if(is_human_[h]) {
			unsigned int tmp;
			printf("player %i:\n", h);
			scanf("%x", &tmp);
			c = tmp;
			if(!is_valid(c)) abort();
			printf("player %i played the %s\n", h, card_string(c));

			// play
			trick_.push_back(c);
			h = (h+1) % hands;

		} else {
			printf("not impl\n");
			abort();			
		}
	}
	
	unsigned char high_trump = 0;
	int winner;
	
	for(int j = 0; j < hands; j++) {
		// player index
		int k = (j + i) % hands;

		unsigned char c = trick_[j];
		
		if((c >> 4) != lead) continue;
		
		if((c & 0xf) > high_trump) {
			high_trump = c & 0xf;
			winner = k;
		}
	}
	
	printf("player %i takes the trick with the %s\n", winner, card_string((lead << 4) + high_trump));

	return winner;
}






