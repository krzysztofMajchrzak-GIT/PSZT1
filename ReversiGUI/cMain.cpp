#include "cMain.h"
#include <wx/bmpbuttn.h>
#include <wx/artprov.h>
#include "player.h"
#include "position.h"




wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_BUTTON(10001, OnButtonClicked)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "REVERSI", wxPoint(30,30), wxSize(700, 700))
{
	/*Czêsc odpowiedzialna za wyswietlanie bierek*/
	wxInitAllImageHandlers();
	wxImage pustePole(wxT("pustePole.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaB(wxT("bierkaB.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaC(wxT("bierkaC.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaP(wxT("bierkaP.png"), wxBITMAP_TYPE_PNG);
	/*Czêsc odpowiedzialna za wyswietlanie bierek*/

	grid = new wxGridSizer(nFieldWidth + 1, nFieldHeight, 5, 5);

	for(int x = 0; x < nFieldWidth; x++)
		for (int y = 0; y < nFieldHeight; y++)
		{
			btn[x][y] = new wxButton(this, 10000 + (y*nFieldWidth + x), "");
			btn[x][y]->SetBitmapLabel(pustePole);

			if (y == 3 && x == 3 || y == 4 && x == 4) // Ustawienie startowe
			{
				btn[x][y]->SetBitmapLabel(bierkaB);
				table[x][y] = white;
			}
			else if (y == 4 && x == 3 || y == 3 && x == 4) // Ustawienie startowe
			{
				btn[x][y]->SetBitmapLabel(bierkaC);
				table[x][y] = black;
			}
			else
				table[x][y] = none;


			grid->Add(btn[x][y], 1, wxEXPAND | wxALL);

			btn[x][y]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this); // Podlaczamy event system

		}
	/*Sekcja na przyciski z do³u*/
	reset = new wxButton(this, 2, "Zresetuj");
	end = new wxButton(this, 1, "Zakoncz");
	
	grid->Add(end, 1, wxEXPAND | wxALL);
	grid->Add(reset, 1, wxEXPAND | wxALL);
	
	reset->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
	end->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnButtonClicked, this);
	
	for (int i = 0; i < 4; i++) // tutaj robie separatory na dole
	{
		wxButton *separator = new wxButton(this, wxID_ANY, "");
		separator->SetBackgroundColour("Grey");
		separator->Enable(false);
		grid->Add(separator, 1, wxEXPAND | wxALL);

	}
	
	whiteCounterButton = new wxButton(this, wxID_ANY, std::to_string(whiteCounter));
	whiteCounterButton->SetBackgroundColour("White");
	whiteCounterButton->Enable(false);
	
	blackCounterButton = new wxButton(this, wxID_ANY, std::to_string(blackCounter));
	blackCounterButton->SetBackgroundColour("Black");
	blackCounterButton->SetForegroundColour("White");
	blackCounterButton->Enable(false);

	grid->Add(whiteCounterButton, 2, wxEXPAND | wxALL);
	grid->Add(blackCounterButton, 2, wxEXPAND | wxALL);

	/*Koniec sekcji na przyciski z do³u*/
	
	this->SetSizer(grid);
	grid->Layout();
	
	// Czêœæ odpowiedzialna za pocz¹tkowe uruchomienie gry

	getStartConfig(Player::player, Player::player);
	blackCounterButton->SetLabel(std::to_string(player[1].getScore()));
	whiteCounterButton->SetLabel(std::to_string(player[0].getScore()));
	nextPlayer();
	makeProposalFor();

}


cMain::~cMain()
{
}

void cMain::getStartConfig(Player::who player1, Player::who player2) // Funkcja Czara z table
{
	player[0] = player1;
	player[1] = player2;
}

bool cMain::isGameOver() // Funkcja Czara z table
{
	return gameOver;
}

void cMain::nextPlayer()  // Funkcja Czara z table
{
	if (whoseMove == whitePlayer)
	{
		whoseMove = blackPlayer;
	}
	else
	{
		whoseMove = whitePlayer;
	}
}

void cMain::makeProposalFor() // Funkcja Czara z table
{
	/*Czêsc odpowiedzialna za wyswietlanie bierek*/
	wxInitAllImageHandlers();
	wxImage pustePole(wxT("pustePole.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaB(wxT("bierkaB.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaC(wxT("bierkaC.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaP(wxT("bierkaP.png"), wxBITMAP_TYPE_PNG);
	/*Czêsc odpowiedzialna za wyswietlanie bierek*/

	canMove = 0;
	for (int i = 0; i < TABLE_SIZE; ++i)
	{
		for (int j = 0; j < TABLE_SIZE; ++j)
		{
			if (table[i][j] == proposal)
			{
				btn[i][j]->SetBitmapLabel(pustePole); // Ustawiamy obrazek pola
				table[i][j] = none;
			}
		}
	}
	for (int i = 0; i < TABLE_SIZE; ++i)
	{
		for (int j = 0; j < TABLE_SIZE; ++j)
		{
			if (table[i][j] == static_cast<pawn>(whoseMove))
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

void cMain::makeProposalForPawn(Position pawnPos, int directionX, int directionY) // Funkcja Czara z table
{
	pawnPos.movePosition(directionX, directionY);
	if (table[pawnPos.getX()][pawnPos.getY()] != opposite())
	{
		return;
	}
	/*Czêsc odpowiedzialna za wyswietlanie bierek*/
	wxInitAllImageHandlers();
	wxImage pustePole(wxT("pustePole.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaB(wxT("bierkaB.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaC(wxT("bierkaC.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaPB(wxT("bierkaPB.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaPC(wxT("bierkaPC.png"), wxBITMAP_TYPE_PNG);
	/*Czêsc odpowiedzialna za wyswietlanie bierek*/

	pawnPos.movePosition(directionX, directionY);
	while (!pawnPos.outOfBorder(TABLE_SIZE))
	{
		if (table[pawnPos.getX()][pawnPos.getY()] == opposite())
		{
			pawnPos.movePosition(directionX, directionY);
		}
		else
		{
			break;
		}
	}
	if (table[pawnPos.getX()][pawnPos.getY()] == none)
	{
		table[pawnPos.getX()][pawnPos.getY()] = proposal;
		if (static_cast<pawn>(whoseMove) == white)
		{
			btn[pawnPos.getX()][pawnPos.getY()]->SetBitmapLabel(bierkaPB); // Ustawiamy obrazek przycisku na podpowiedz dla bialych
		}
		else if (static_cast<pawn>(whoseMove) == black)
		{
			btn[pawnPos.getX()][pawnPos.getY()]->SetBitmapLabel(bierkaPC); // Ustawiamy obrazek przycisku na podpowiedz dla czarnych
		}
		
		++canMove;
	}
}

bool cMain::makeMove(Position pawnPos) // Funkcja Czara z Table
{
	if (!canMove)
	{
		return false;
	}
	//DC pawnPos if computer
	if (player[whoseMove] == Player::computer)
	{
		//TODO
	}
	else
	{
		makeMovePlayer(pawnPos);
	}
	updateScore();
	return true;
}

void cMain::makeMovePlayer(Position pawnPos) // Funkcja Czara z Table
{
	/*Czêsc odpowiedzialna za wyswietlanie bierek*/
	wxInitAllImageHandlers();
	wxImage pustePole(wxT("pustePole.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaB(wxT("bierkaB.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaC(wxT("bierkaC.png"), wxBITMAP_TYPE_PNG);
	/*Czêsc odpowiedzialna za wyswietlanie bierek*/

	if (table[pawnPos.getX()][pawnPos.getY()] == proposal)
	{
		table[pawnPos.getX()][pawnPos.getY()] = static_cast<pawn>(whoseMove);
		if (static_cast<pawn>(whoseMove) == white)
		{
			btn[pawnPos.getX()][pawnPos.getY()]->SetBitmapLabel(bierkaB); // Ustawiamy przycisk na biala bierke
		}
		else if (static_cast<pawn>(whoseMove) == black)
		{
			btn[pawnPos.getX()][pawnPos.getY()]->SetBitmapLabel(bierkaC); // Ustawiamy przycisk na czarna bierke
		}
		
		changePawnColor(pawnPos); // Moja poprawka
	}
	
}

void cMain::updateScore() // Funkcja Czara z Table
{
	player[0].scoreClear();
	player[1].scoreClear();
	for (int i = 0; i < TABLE_SIZE; ++i)
	{
		for (int j = 0; j < TABLE_SIZE; ++j)
		{
			if (table[i][j] == white)
			{
				++player[0];
			}
			else if (table[i][j] == black)
			{
				++player[1];
			}
		}
	}
}

void cMain::changePawnColor(Position pawnPos) // Funkcja Czara z Table
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

void cMain::changePawnInDirection(Position pawnPos, int directionX, int directionY) // Funkcja Czara z Table
{
	/*Czêsc odpowiedzialna za wyswietlanie bierek*/
	wxInitAllImageHandlers();
	wxImage pustePole(wxT("pustePole.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaB(wxT("bierkaB.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaC(wxT("bierkaC.png"), wxBITMAP_TYPE_PNG);
	/*Czêsc odpowiedzialna za wyswietlanie bierek*/
	
	pawnPos.movePosition(directionX, directionY);
	if (table[pawnPos.getX()][pawnPos.getY()] != opposite())
	{
		return;
	}
	pawnPos.movePosition(directionX, directionY);
	while (!pawnPos.outOfBorder(TABLE_SIZE))
	{
		if (table[pawnPos.getX()][pawnPos.getY()] == static_cast<pawn>(whoseMove))
		{
			pawnPos.movePosition(-directionX, -directionY);
			while (table[pawnPos.getX()][pawnPos.getY()] == opposite())
			{
				table[pawnPos.getX()][pawnPos.getY()] = static_cast<pawn>(whoseMove);
				if (static_cast<pawn>(whoseMove) == white)
				{
					btn[pawnPos.getX()][pawnPos.getY()]->SetBitmapLabel(bierkaB); // Ustawiamy przycisk na bierke biala
				}
				else if (static_cast<pawn>(whoseMove) == black)
				{
					btn[pawnPos.getX()][pawnPos.getY()]->SetBitmapLabel(bierkaC); // Ustawiamy przycisk na bierke czarna
				}
				pawnPos.movePosition(-directionX, -directionY);
			}
			return;
		}
		pawnPos.movePosition(directionX, directionY);
	}
}

cMain::pawn cMain::opposite() // Funkcja Czara z Table
{
	if (whoseMove == whitePlayer)
	{
		return black;
	}
	return white;
}

void cMain::checkWinCondition() // Funkcja Czara z Table
{
	if (player[0].getScore() == 0 || player[1].getScore() == 0 || canMove == 0 || player[0].getScore() + player[1].getScore() == TABLE_SIZE * TABLE_SIZE)
	{
		
		if (player[0].getScore() > player[1].getScore())
		{
			wxMessageBox("Player WHITE wins the game!"); // Wyswietlanie komunikatu o wygranej bialego gracza
		}
		else
			wxMessageBox("Player BLACK wins the game!"); // Wyswietlanie komunikatu o wygranej czarnego gracza

		gameOver = true;
		resetGame(); // Wywoluje funkcje resetujaca cala gre

	}

}

void cMain::OnButtonClicked(wxCommandEvent &evt)
{

	if (evt.GetId() == 1) // Kliknelismy przycisk end
	{
		Destroy();
	}
	else if (evt.GetId() == 2) // Kliknelismy przycisk reset
	{
		resetGame();
	}

	else // Tutaj normalna gra
	{
		int x = (evt.GetId() - 10000) % nFieldWidth; // Pobieram wspolrzedna x kliknietego przycisku
		int y = (evt.GetId() - 10000) / nFieldWidth; // pobieram wspolrzedna y kliknietego przycisku
		if (table[x][y] == proposal) // Za kazdym razem gdy klikniete zostanie pole proposal, wykonywany jest normalny cykl growy jak w petli while
		{
			//Wszystkie elementy skopiowane z twojej petli while
			makeMove(Position(x, y));
			nextPlayer();
			makeProposalFor();
			blackCounterButton->SetLabel(std::to_string(player[1].getScore()));
			whiteCounterButton->SetLabel(std::to_string(player[0].getScore()));
			checkWinCondition();
		}
	}
	
	evt.Skip();
}

void cMain::resetGame() // Funkcja resetujaca cala plansze do poziomu poczatkowego
{
	/*Czêsc odpowiedzialna za wyswietlanie bierek*/
	wxInitAllImageHandlers();
	wxImage pustePole(wxT("pustePole.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaB(wxT("bierkaB.png"), wxBITMAP_TYPE_PNG);
	wxImage bierkaC(wxT("bierkaC.png"), wxBITMAP_TYPE_PNG);
	/*Czêsc odpowiedzialna za wyswietlanie bierek*/


	for (int x = 0; x < nFieldWidth; x++) // W tej petli poustawiam wszystkie obrazki w tablicy btn i wszystkie znaczniki w table jak na poczatku
		for (int y = 0; y < nFieldHeight; y++)
		{
			btn[x][y]->SetBitmapLabel(pustePole);

			if (y == 3 && x == 3 || y == 4 && x == 4) // Poczatkowe polozenie bierek
			{
				btn[x][y]->SetBitmapLabel(bierkaB);
				table[x][y] = white;

			}
			else if (y == 4 && x == 3 || y == 3 && x == 4) // Poczatkowe polozeni bierek
			{
				btn[x][y]->SetBitmapLabel(bierkaC);
				table[x][y] = black;
				//btn[y, x]->Enable(false); // zamiast tego bedziemy programowac konkretna funkcjonalnosc
			}
			else
				table[x][y] = none;
		}
	/*Pierwsze wywolanie przy poczatkowym ustawieniu*/
	getStartConfig(Player::player, Player::player);
	blackCounterButton->SetLabel(std::to_string(player[1].getScore()));
	whiteCounterButton->SetLabel(std::to_string(player[0].getScore()));
	nextPlayer();
	makeProposalFor();
	/*Pierwsze wywolanie przy poczatkowym ustawieniu*/
}


