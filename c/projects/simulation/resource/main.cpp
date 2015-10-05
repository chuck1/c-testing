#include <vector>
#include <memory>

#include <glm/glm.hpp>

class Player
{
public:
	glm::vec2	_M_position;
};

typedef std::weak_ptr<Player> W_P;

class Connection
{
public:
	Connection(W_P p0, W_P p1, float w):
		_M_weight(w)
	{
		_M_players[0] = p0;
		_M_players[1] = p1;
	}
	float	length()
	{
		auto p0 = _M_players[0].lock();
		auto p1 = _M_players[1].lock();
		assert(p0);
		assert(p1);
		return glm::length(p0->_M_position - p1->_M_position);
	}

	W_P	_M_players[2];
	float	_M_weight;
};

typedef std::shared_ptr<Connection> S_C;

class Sim
{
public:
	std::vector<S_C>	_M_connections;
};

int main()
{
	
	
	return 0;
}

