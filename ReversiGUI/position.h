#pragma once
#ifndef POSITION_H_
#define POSITION_H_



class Position
{
public:
	Position();
	Position(int posX, int posY);
	~Position();
	void movePosition(int posX, int posY);
	bool outOfBorder(int maxPos);
	int getX();
	int getY();
private:
	int x;
	int y;

};

#endif //POSITION_H_
