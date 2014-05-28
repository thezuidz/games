#ifndef _Game
#define _Game

#include CRandom
#include CScreen

using namespace std;

class Game // abstract base class for games
{

	protected:
		CScreen S;      // screen handler
		CRandom R;    //random # generator
		int gameType; // identifies the game
		int *playerScore; // array of player scores - dynamically created
		int nbrPlayers; // # of players in the game

	public:
		Game(int type, int players = 1);
		~Game();
		int getScore(int playerNbr); // return the score for a player
		void updateScore(int playerNbr, int amt); // adds or subtracts amt form a player's score

		// abstract methods - must be overridden
		virtual void playGame() = 0; // start playing the game
		virtual void endGame() = 0; // end the game

		// other methods as needed

}

#endif