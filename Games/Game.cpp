// Bilal Adra & Eric Zuidema
// CSC306 - Games Project
// Base Class

#include "Game.h"

Game::Game(int type, int players = 1)
{
	gameType = type;
	nbrPlayers = players;

	// Set # players
	playerScore = new int[nbrPlayers];
	
	// Initialize all scores to 0
	for(int i = 0; i < nbrPlayers; i++)
	{
		playerScore[i] = 0;
	}
}

Game::~Game()
{
	delete [] playerScore;
}

int Game::getScore(int playerNbr)
{
	return playerScore[playerNbr];
}

void Game::updateScore(int playerNbr, int amt)
{
	playerScore[playerNbr] += amt;
}



