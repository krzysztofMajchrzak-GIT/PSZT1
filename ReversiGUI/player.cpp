#include "player.h"

Player::Player()
{
	playerType = player;
	score = 2;
}

Player::~Player()
{

}

Player::Player(who w)
{
	playerType = w;
	score = 2;
}

Player & Player::operator=(const Player & p)
{
	playerType = p.playerType;
	score = p.score;
	return *this;
}

bool Player::operator==(const Player &p)
{
	if (playerType == p.playerType)
	{
		return true;
	}
	return false;
}

void Player::scoreClear()
{
	score = 0;
}

Player & Player::operator++()
{
	++score;
	return *this;
}


int Player::getScore()
{
	return score;
}