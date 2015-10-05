
#include <random>
#include <algorithm>
#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <Deck.hpp>

Deck::Deck()
{
}

void Deck::init(int humans, int computers)
{
	char buffer[32];
	
	// populate the deck
	for(unsigned char suit = 0; suit < 4; suit++) {
		for(unsigned char i = 0; i < 13; i++) {
			cards_.emplace_back(new Card(suit, + i));
		}
	}

	int j = 0;

	players_.clear();
	for(int i = 0; i < humans; i++) {
		sprintf(buffer, "player_%i", j++);
		//players_.push_back(new Human(buffer));
		players_.push_back(new Human(buffer));
	}
	for(int i = 0; i < computers; i++) {
		sprintf(buffer, "player_%i", j++);
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

	for(int j = 0; j < hands; j++) {
		players_[j]->reset(*this);
	}

	int k = 0;
	for(int i = 0; i < cards_per_hand; i++) {
		for(int j = 0; j < hands; j++) {
			S_C c = cards_[k++];
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
	S_C c = find_card(0,0);

	for(int i = 0; i < players_.size(); i++) {
		//for(int j = 0; j < players_[i]->hand_.size(); j++) {
			//Card & c = players_[i]->hand_[j];
			//if((c.suit_ == 0) && (c.value_ == 0)) return i;
		//}
		if(players_[i]->has_card_in_hand(c)) return i;
	}

	return -1;
}

int		Deck::play(int i, S_C first_card)
{
	player_lead_ = i;
	player_current_ = i;
	
	int players = players_.size();
	//Card & c;

	std::vector<S_C> trick(players, 0);
	
		
	if(verbose_) printf("\n");

	trick_.clear();

	for(unsigned int j = 0; j < players; j++) {
		printf("%20s", players_[j]->name_);
	}
	printf("\n");


	if(first_card) {
		// used to force playing the two of clubs

		// remove card from player's hand
		players_[player_current_]->remove_from_hand(first_card);

		// play
		trick_.push_back(first_card);
		lead_ = first_card->suit_;
		trick[player_current_] = first_card;

		// advance player index
		player_current_ = (player_current_+1) % players;
	} else {
		// play a card
		// this is a virtual function that is derived for human and computer players
		S_C c = players_[player_current_]->play(*this, true);

		if(verbose_) printf("player %i leads with the %s\n", 
				player_current_, c->string());

		// play
		trick_.push_back(c);
		lead_ = c->suit_;
		trick[player_current_] = c;

		// advance player index
		player_current_ = (player_current_+1) % players;
		
	}
	
	for(unsigned int j = 0; j < players; j++) {
		auto c = trick[j];
		if(c) {
			printf("%20s", c->string());
		} else {
			printf("%20s", "");
		}
	}
	printf("\n");

	if(verbose_) printf("%s are lead\n", lead_.string());

	// loop back to i
	while(player_current_ != i) {	
		// play a card
		S_C c = players_[player_current_]->play(*this, false);

		if(verbose_) printf("player %i played the %s\n",
				player_current_, c->string());


		// play
		trick_.push_back(c);
		trick[player_current_] = c;
		// advance player index
		player_current_ = (player_current_+1) % players;

		for(unsigned int j = 0; j < players; j++) {
			auto c = trick[j];
			if(c) {
				printf("%20s", c->string());
			} else {
				printf("%20s", "");
			}
		}
		printf("\n");
	}


	int high_trump = -1;
	int winner = -1;
	int winner_card = -1;

	assert(trick_.size() == players);



	for(int j = 0; j < players; j++) {
		// player index
		int k = (j + i) % players;

		S_C c = trick_[j];

		if(verbose_) printf("%s\n", c->string());


		if(c->suit_ != lead_) continue;

		if(c->value_ > high_trump) {
			high_trump = c->value_;
			winner = k;
			winner_card = j;
		}
	}


	assert(winner > -1);
	assert(winner_card > -1);

	assert(winner_card < trick_.size());

	if(verbose_) printf(
			"player %i takes the trick with the %s\n",
			winner,
			trick_[winner_card]->string());

	// give winner the cards
	std::copy(trick_.begin(), trick_.end(), std::back_inserter(players_[winner]->pile_));

	return winner;
}

void		Deck::play_hand()
{
	for(int i = 0; i < players_.size(); i++) {
		Player & p = *players_[i];
		printf("%2i ", p.cum_score_);
	}
	printf("\n");

	// hand

	deal();

	int i = whos_got_the_two();
	//if(i < 0) return i;

	if(verbose_) printf("%i has the two\n", i);

	S_C c = find_card(0,0);

	// play the two
	i = play(i, c);

	// play all tricks
	while(cards_in_hand() > 0) {
		i = play(i);
	}

	int tmp = 0;
	int tmp_score = 0;
	// save the scores
	for(int i = 0; i < players_.size(); i++) {
		Player & p = *players_[i];

		p.cum_score_ += p.score();
		tmp_score += p.score();

		tmp += p.pile_.size();
		p.pile_.clear();
	}

	assert(tmp_score == 26);
	assert(tmp == 52);

}
S_C			Deck::find_card(Suit s, unsigned char v)
{
	for(auto card : cards_) {
		if(card->suit_ == s) {
			if(card->value_ == v) return card;
		}
	}
	assert(0);
	return S_C();
}



