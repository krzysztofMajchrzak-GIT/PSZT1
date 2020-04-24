#ifndef TABLE_H_
#define TABLE_H_

#define TABLE_SIZE 8

#include "position.h"
#include "player.h"

#define DEBUG
#ifdef DEBUG
#include <iostream>
#endif //DEBUG

class Position;
class Player;

class Table
{
public:
    Table();
    ~Table();
    enum pawn {white, black, proposal, none};

    enum color {whitePlayer, blackPlayer};

    void getStartConfig(Player::who player1, Player::who player2);
    bool isGameOver();
    void nextPlayer();
    void makeProposalFor();
    bool makeMove(Position pawnPos);
    void updateScore();
    void checkWinCondition();
    #ifdef DEBUG
    void printTable();
    #endif //DEBUG

private:
    Player player[2];
    pawn table[TABLE_SIZE][TABLE_SIZE];
    color whoWin;
    int canMove;
    color whoseMove;
    bool gameOver;
    void makeProposalForPawn(Position pawnPos, int directionX, int directionY);
    void makeMovePlayer(Position pawnPos);
    void changePawnColor(Position pawnPos);
    void changePawnInDirection(Position pawnPos, int directionX, int directionY);
    pawn opposite();

};

#endif //TABLE_H_


