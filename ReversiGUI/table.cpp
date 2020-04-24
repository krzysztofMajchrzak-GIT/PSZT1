#include "table.h"
#include "AI.h"

#define DEBUG

Table::Table()
{
    for(int i = 0; i < TABLE_SIZE; ++i)
    {
        for(int j = 0; j < TABLE_SIZE; ++j)
        {
            table[i][j] = none;
        }
    }
    table[3][3] = table[4][4] = white;
    table[4][3] = table[3][4] = black;
    player[0] = player[1] = Player();
    whoWin = whitePlayer;
    canMove = 0;
    whoseMove = whitePlayer;
    gameOver = false;
	maxDepth = 1;
}

Table::~Table()
{
}

void Table::getStartConfig(Player::who player1, Player::who player2)
{
    player[0] = player1;
    player[1] = player2;
}

bool Table::isGameOver()
{
    return gameOver;
}

void Table::nextPlayer()
{
    if(whoseMove == whitePlayer)
    {
        whoseMove = blackPlayer;
    }
    else
    {
        whoseMove = whitePlayer;
    }
}

void Table::makeProposalFor()
{
    canMove = 0;
    for(int i = 0; i < TABLE_SIZE; ++i)
    {
        for(int j = 0; j < TABLE_SIZE; ++j)
        {
            if(table[i][j] == proposal)
            {
                table[i][j] = none;
            }
        }
    }
    for(int i = 0; i < TABLE_SIZE; ++i)
    {
        for(int j = 0; j < TABLE_SIZE; ++j)
        {
            if(table[i][j] == static_cast<pawn>(whoseMove))
            {
                makeProposalForPawn(Position(i, j), -1, -1);
                makeProposalForPawn(Position(i, j), -1, 0);
                makeProposalForPawn(Position(i, j), -1, 1);
                makeProposalForPawn(Position(i, j), 0, -1);
                makeProposalForPawn(Position(i, j), 0, 1);
                makeProposalForPawn(Position(i, j), 1, -1);
                makeProposalForPawn(Position(i, j), 1, 0);
                makeProposalForPawn(Position(i, j), 1, 1);
            }
        }
    }
}

void Table::makeProposalForPawn(Position pawnPos, int directionX, int directionY)
{
    pawnPos.movePosition(directionX, directionY);
    if(table[pawnPos.getX()][pawnPos.getY()] != opposite())
    {
        return;
    }
    pawnPos.movePosition(directionX, directionY);
    while(!pawnPos.outOfBorder(TABLE_SIZE))
    {
        if(table[pawnPos.getX()][pawnPos.getY()] == opposite())
        {
            pawnPos.movePosition(directionX, directionY);
        }
        else
        {
            break;
        }
    }
    if(table[pawnPos.getX()][pawnPos.getY()] == none  && !pawnPos.outOfBorder(TABLE_SIZE))
    {
        table[pawnPos.getX()][pawnPos.getY()] = proposal;
        ++canMove;
    }
}

bool Table::makeMove(Position pawnPos)
{
    //DC pawnPos if computer
    if(player[whoseMove] == Player::computer)
    {
        AI ai;
        makeMovePlayer(ai.makeMove(*this));
    }
    else
    {
        makeMovePlayer(pawnPos);
    }
    updateScore();
    return true;
}

void Table::makeAIMove(Position pawnPos)
{
    makeMovePlayer(pawnPos);
    updateScore();
}

void Table::makeMovePlayer(Position pawnPos)
{
	if (!canMove)
	{
		return;
	}
    if(table[pawnPos.getX()][pawnPos.getY()] == proposal)
    {
        table[pawnPos.getX()][pawnPos.getY()] = static_cast<pawn>(whoseMove);
    }
    changePawnColor(pawnPos);
}

void Table::updateScore()
{
    player[0].scoreClear();
    player[1].scoreClear();
    for(int i = 0; i < TABLE_SIZE; ++i)
    {
        for(int j = 0; j < TABLE_SIZE; ++j)
        {
            if(table[i][j] == white)
            {
                ++player[0];
            }
            else if(table[i][j] == black)
            {
                ++player[1];
            }
        }
    }
}

void Table::changePawnColor(Position pawnPos)
{
    changePawnInDirection(pawnPos, -1, -1);
    changePawnInDirection(pawnPos, -1, 0);
    changePawnInDirection(pawnPos, -1, 1);
    changePawnInDirection(pawnPos, 0, -1);
    changePawnInDirection(pawnPos, 0, 1);
    changePawnInDirection(pawnPos, 1, -1);
    changePawnInDirection(pawnPos, 1, 0);
    changePawnInDirection(pawnPos, 1, 1);
}

void Table::changePawnInDirection(Position pawnPos, int directionX, int directionY)
{
    pawnPos.movePosition(directionX, directionY);
    if(table[pawnPos.getX()][pawnPos.getY()] != opposite())
    {
        return;
    }
    pawnPos.movePosition(directionX, directionY);
    while(!pawnPos.outOfBorder(TABLE_SIZE))
    {
        if(table[pawnPos.getX()][pawnPos.getY()] == static_cast<pawn>(whoseMove))
        {
            pawnPos.movePosition(-directionX, -directionY);
            while(table[pawnPos.getX()][pawnPos.getY()] == opposite())
            {
                table[pawnPos.getX()][pawnPos.getY()] = static_cast<pawn>(whoseMove);
                pawnPos.movePosition(-directionX, -directionY);
            }
            return;
        }
        pawnPos.movePosition(directionX, directionY);
    }
}

Table::pawn Table::opposite()
{
    if(whoseMove == whitePlayer)
    {
        return black;
    }
    return white;
}

void Table::checkWinCondition()
{
    if(player[0].getScore() == 0 || player[1].getScore() == 0 || player[0].getScore() + player[1].getScore() == TABLE_SIZE * TABLE_SIZE)
    {
        gameOver = true;
    }

}

std::vector<Position> Table::makeAllPossibleMoves()
{
    std::vector<Position> temp;
    for (int i = 0; i < TABLE_SIZE; ++i)
    {
        for (int j = 0; j < TABLE_SIZE; ++j)
        {
            if (table[i][j] == proposal)
            {
                temp.push_back(Position(i, j));
            }
        }
    }
    return temp;
}

int Table::getP1Score()
{

    return player[0].getScore();
}
int Table::getP2Score()
{
    return player[1].getScore();
}

int Table::retScoreDiff()
{
    if (static_cast<int>(whoseMove) == 0)
    {
        return getP1Score() - getP2Score();
    }
    return getP2Score() - getP1Score();
}

bool Table::canPlayerMove()
{
    return static_cast<bool>(canMove);
}


void Table::printTable()
{
    for(int i = 0; i < TABLE_SIZE; ++i)
    {
        for(int j = 0; j < TABLE_SIZE; ++j)
        {
            std::cout<<table[i][j];
        }
        std::cout<<std::endl;
    }
}
int Table::getMaxDepth()
{
	return maxDepth;
}

void Table::incrementMaxDepth()
{
	if (maxDepth == 5)
		maxDepth = 1;
	else
		maxDepth++;
}

