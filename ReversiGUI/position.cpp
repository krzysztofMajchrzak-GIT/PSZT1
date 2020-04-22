#include "position.h"

Position::Position()
{

}

Position::~Position()
{

}

Position::Position(int posX, int posY)
{
	x = posX;
	y = posY;
}

void Position::movePosition(int posX, int posY)
{
	x += posX;
	y += posY;
}

bool Position::outOfBorder(int maxPos)
{
	if (x < 0 || y < 0 || x > maxPos || y > maxPos)
	{
		return true;
	}
	return false;
}

int Position::getX()
{
	return x;
}

int Position::getY()
{
	return y;
}