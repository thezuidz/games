#ifndef   _wheelOfMisfortune
#define   _wheelOfMisfortune

#include "Game.h"
#include <string>

class wheelOfMisfortune:protected Game
{
private:
	char   ltrsUsed[26];
	int	   numLtrsUsed;
	int    vowelsUsed;
	int    lastWinner;
	string blanksInLines[4];
	string phrases[15];
	
	void drawPlayer(int playerNum, bool isTurn);
	void drawMenu();
	void drawPhrase(string phrase);
	void drawLettersRemaining(char ltrUsed);
	void drawWheel(int num);//func to draw wheel when its on a number
	void fillBlank(char ltr, string phrase);
	void loadPhrases();
	int  spin(); //returns 10 if theres a problem
	bool isVowel(char ltr);
	bool isInPhrase(char ltr, string phrase, int &occurence);
	bool isTaken(char ltr);
	bool checkPhrase(string input, string phrase);

public:
	wheelOfMisfortune(int nbrPlayers = 2):Game(1, nbrPlayers)
	{
		numLtrsUsed = 0; 
		vowelsUsed = 0;
		memset(ltrsUsed, 0x00, sizeof(char)*26); 
		memset(blanksInLines, 0x00, sizeof(string)*4);
		memset(phrases, 0x00, sizeof(string)*15);

		loadPhrases();
		playGame(); 
	};
	~wheelOfMisfortune();
	void display();
	void playGame();//plays game with user
	void endGame();
};

#endif;

