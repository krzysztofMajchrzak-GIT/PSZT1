#pragma once

#include "wx/wx.h"
#include "player.h"
#include "position.h"
#include "table.h"

#define TABLE_SIZE 8
#include <iostream>

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

public:
	int nFieldWidth = TABLE_SIZE;
	int nFieldHeight = TABLE_SIZE;
	int whiteCounter; // licznik punktow
	int blackCounter; // Licznik punktow
	wxButton *btn[TABLE_SIZE][TABLE_SIZE]; // Nasza plansza przyciskow
	wxButton *blackCounterButton; // pole liczace punkt gracza czarnego
	wxButton *whiteCounterButton; // Pole liczace punkty gracza bialego
	wxButton *reset; // Przycisk resettujacy gre
	wxButton *end; // Przycisk wylaczajacy gre
	wxGridSizer *grid;
	wxButton *playerChoiceButton;
	wxButton *ComputerChoiceButton;
	Table *recordTable; // Twoja tablica do sledzenia rozgrywki
	Player tempPlayer[2]; // Pomocniczy Player do poczatkowej konfiguracji

	
	enum pawn { white, black, proposal, none };

	enum color { whitePlayer, blackPlayer };

	void OnButtonClicked(wxCommandEvent &evt); // Nasz event system
	void resetGame(); // Metoda resetujaca gre
	wxDECLARE_EVENT_TABLE(); // Inicjalizacja tabeli eventow

	// Czêœæ od CZARA z table przelozona na cMain
public:
	void getStartConfig(Player::who player1, Player::who player2);
	bool isGameOver();
	void nextPlayer();
	void makeProposalFor();
	bool makeMove(Position pawnPos);
	void updateScore();
	void checkWinCondition();

public:
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

