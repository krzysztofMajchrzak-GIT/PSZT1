#pragma once
#ifndef PLAYER_H_
#define PLAYER_H_

class Player
{
public:
	enum who { player, computer };
	Player();
	~Player();
	Player(who w);
	Player & operator=(const Player &);
	bool operator==(const Player &p);
	void scoreClear();
	Player & operator ++();
	int getScore();
private:
	int score;
	who playerType;

};

#endif //PLAYER_H_