#ifndef HEARTS_PLAYER_HPP
#define HEARTS_PLAYER_HPP

#include <Card.hpp>

class Player
{
	public:
		Player(): is_human_(true) {}
		bool			is_human_;
		std::vector<Card>	hand_;
		std::vector<Card>	pile_;
};

#endif
