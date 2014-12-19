
#include <random>
#include <algorithm>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <Deck.hpp>

Deck::Deck()
{
}

void Deck::init(int hands)
{
	char buffer[32];

	for(unsigned char suit = 0; suit < 4; suit++) {
		for(unsigned char i = 0; i < 13; i++) {
			cards_.push_back(Card(suit, + i));
		}
	}

	players_.clear();
	for(int i = 0; i < hands; i++) {
		sprintf(buffer, "player_%i", i);
		//players_.push_back(new Human(buffer));
		players_.push_back(new Computer(buffer));
	}
}

void Deck::deal()
{
	hearts_broken_ = false;
	int hands = players_.size();
	int cards_per_hand = 52 / hands;

	int extra = 52 % hands;


	// shuffle the cards
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(cards_.begin(), cards_.end(), g);


	int k = 0;
	for(int i = 0; i < cards_per_hand; i++) {
		for(int j = 0; j < hands; j++) {
			Card c = cards_[k++];
			players_[j]->give_card(c); //hand_.push_back(c);
			
			//if(verbose_) printf("%X %X    ", c.suit_, c.value_);
		}
		if(verbose_) printf("\n");
	}

	for(int j = 0; j < hands; j++)
		players_[j]->sort_hand();

	/*
	for(int i = 0; i < cards_per_hand; i++) {
		for(int j = 0; j < hands; j++) {
			Card c = players_[j]->hand_[i];
			if(verbose_) printf("%X %X    ", c.suit_, c.value_);
		}
		if(verbose_) printf("\n");
	}
	*/
}



int Deck::high_score()
{
	int hs = 0;
	
	for(int i = 0; i < players_.size(); i++) {
		int s = players_[i]->cum_score_; // + players_[i]->score();
		if(s > hs) hs = s;
	}

	return hs;
}

int		Deck::cards_in_hand()
{
	assert(players_.size() > 0);
	return players_[0]->cards_in_hand();
}

int Deck::whos_got_the_two()
{
	for(int i = 0; i < players_.size(); i++) {
		//for(int j = 0; j < players_[i]->hand_.size(); j++) {
			//Card & c = players_[i]->hand_[j];
			//if((c.suit_ == 0) && (c.value_ == 0)) return i;
		//}
		if(players_[i]->has_card_in_hand(Card(0,0))) return i;
	}

	return -1;
}

int Deck::play(int i, Card * first_card)
{
	player_lead_ = i;
	player_current_ = i;
	
	int players = players_.size();
	//Card & c;

	if(verbose_) printf("\n");

	trick_.clear();

	if(first_card) {
		// remove card from player's hand
		players_[player_current_]->remove_from_hand(*first_card);

		// play
		trick_.push_back(*first_card);
		lead_ = first_card->suit_;
		player_current_ = (player_current_+1) % players;
	} else {
		// play a card
		// this is a virtual function that is derived for human and computer players
		Card c = players_[player_current_]->play(*this, true);

		if(verbose_) printf("player %i leads with the %s\n", 
				player_current_, c.string());

		// play
		trick_.push_back(c);
		lead_ = c.suit_;
		player_current_ = (player_current_+1) % players;

	}

	if(verbose_) printf("%s are lead\n", lead_.string());

	// loop back to i
	while(player_current_ != i) {	
		// play a card
		Card c = players_[player_current_]->play(*this, false);

		if(verbose_) printf("player %i played the %s\n",
				player_current_, c.string());

		// play
		trick_.push_back(c);
		player_current_ = (player_current_+1) % players;
	}


	int high_trump = -1;
	int winner = -1;
	int winner_card = -1;

	assert(trick_.size() == players);

	

	for(int j = 0; j < players; j++) {
		// player index
		int k = (j + i) % players;

		Card c = trick_[j];

		if(verbose_) printf("%s\n", c.string());


		if(c.suit_ != lead_) continue;

		if(c.value_ > high_trump) {
			high_trump = c.value_;
			winner = k;
			winner_card = j;
		}
	}


	assert(winner > -1);
	assert(winner_card > -1);

	assert(winner_card < trick_.size());

	if(verbose_) printf("player %i takes the trick with the %s\n", winner, trick_[winner_card].string());
	
	// give winner the cards
	std::copy(trick_.begin(), trick_.end(), std::back_inserter(players_[winner]->pile_));
	
	return winner;
}






