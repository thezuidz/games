#include "wheelOfMisfortune.h"
#include "CScreen.h"
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

using namespace std;

wheelOfMisfortune::~wheelOfMisfortune()
{
}

void wheelOfMisfortune::display()
{
	S.Box(0, 0, 80, 5, DRED);
	for(int i = 0; i < nbrPlayers; i++)
	{  drawPlayer(i, false);  }

	drawMenu();
	drawLettersRemaining(NULL);
	drawPhrase("");
	S.Box(40, 12, 80, 24, GOLD);//wheel area
}

void wheelOfMisfortune::drawPlayer(int playerNum, bool isTurn)
{
	if(isTurn)
	{ S.Box(playerNum*20, 0, 20*(playerNum+1), 5, GREEN); }
	else
	{ S.Box(playerNum*20, 0, 20*(playerNum+1), 5, DRED);  }

	string playerInfo = "Player" + to_string(playerNum + 1) + " score: " + to_string(getScore(playerNum));
	S.DrawString(playerNum*20, 2, &playerInfo[0]);
}

void wheelOfMisfortune::drawMenu()
{
	S.Box(40, 5, 80, 12, LTGREEN);

	S.DrawString(42,5,"Instructions:");
	S.DrawString(42,6,"Press W to spin the wheel");
	S.DrawString(42,7,"Press S to solve");
}

void wheelOfMisfortune::drawLettersRemaining(char ltrUsed)
{
	string ltr;
	if(ltrUsed != NULL) //so we only change one of the letters
	{
		ltrsUsed[numLtrsUsed] = ltrUsed;
		int loc = ltrUsed - 65;
		ltr = ltrUsed;
		S.GotoXY(1 + (3*loc % 30), 5 + 2*(loc*1/10));
		S.DrawString(1 + (3*loc % 30), 5 + 2*(loc*1/10), &ltr[0],RED,BLACK);
	}
	else //for initial setup
	{
		S.Box(0, 5, 40, 12, GREEN);//remaining letters area

		for(int i = 0; i < 26; i++)
		{
			ltr = (char)(i + 65);
			S.DrawString(1 + (3*i % 30), 5 + 2*(i*1/10), &ltr[0]);
		}
	}
}

void wheelOfMisfortune::drawPhrase(string phrase)
{
	if(strcmp(phrase.c_str(),""))
	{
		//set up vars to parse phrase into separate words
		stringstream sIn(phrase);
		int numWords = count(phrase.begin(), phrase.end(), ' ') + 1;
		string word;

		int wordCtr = 0, ltrsInLine = 0, lines = 0;
		string wordBlanks;
		bool wordIn = true;
		while(wordCtr < numWords)
		{
			if(wordIn && sIn.good())//if last word was entered as blanks and there are still words read another
			{
				word.clear();
				sIn >> word;
				ltrsInLine += word.size();
			}
			if(ltrsInLine <= 20)
			{
				for(int i = 0; i < word.size(); i++)
				{	wordBlanks.append("_ ");  }
				wordBlanks.append("  ");
				ltrsInLine += 2; //adjust for spaces
				wordCtr++;
				wordIn = true;
			}
			else
			{
				//show blanks
				blanksInLines[lines] = wordBlanks;
				wordBlanks = wordBlanks.substr(0, wordBlanks.size() - 3);
				S.DrawString(2, 14 + lines*2, &wordBlanks[0]);

				//reset vars
				ltrsInLine = 0;
				lines++;
				wordBlanks.clear();
				wordIn = false;
			}
		}
		//get the last line
		blanksInLines[lines] = wordBlanks;
		wordBlanks = wordBlanks.substr(0, wordBlanks.size() - 3);
		S.DrawString(2, 14 + lines*2, &wordBlanks[0]);
	}
	else //for initial setup
	{
		S.Box(0, 12, 40, 24, BLUE);//phrase area
		S.DrawString(16, 12, "Puzzle:");
	}
}

int wheelOfMisfortune::spin()
{
	int ret;
	//set range for the amount of times a number is randomly chosen
	R.setRange(15, 10);
	int numSpins = R.fnRand();

	R.setRange(9,-1);
	for(int i = 0; i < numSpins; i++ )//pick a random number b/w 0 and 9 and animate the wheel
	{
		ret = R.fnRand();
		drawWheel(ret);
		Sleep(i*100);
	}
	return ret;
}

void wheelOfMisfortune::drawWheel(int num)
{
	S.Box(40, 12, 80, 24, num%4 +5);

	switch(num)
	{
	case(0)://makes a 0 out of 0s
		S.DrawString(60, 13, "0");
		S.DrawString(58, 13, "0"); S.DrawString(62, 13, "0");
		S.DrawString(56, 14, "0"); S.DrawString(64, 14, "0");
		S.DrawString(54, 15, "0"); S.DrawString(66, 15, "0");
		S.DrawString(54, 16, "0"); S.DrawString(66, 16, "0");
		S.DrawString(54, 17, "0"); S.DrawString(66, 17, "0");
		S.DrawString(54, 18, "0"); S.DrawString(66, 18, "0");
		S.DrawString(54, 19, "0"); S.DrawString(66, 19, "0");
		S.DrawString(54, 20, "0"); S.DrawString(66, 20, "0");
		S.DrawString(56, 21, "0"); S.DrawString(64, 21, "0");
		S.DrawString(58, 22, "0"); S.DrawString(62, 22, "0");
		S.DrawString(60, 22, "0");
		break;
	case(1)://makes a 1 out of 1s
		S.DrawString(60, 13, "11");
		S.DrawString(59, 14, "1"); S.DrawString(61, 14, "1");
		S.DrawString(58, 15, "1"); S.DrawString(61, 15, "1");
		S.DrawString(57, 16, "1"); S.DrawString(61, 16, "1");
		S.DrawString(61, 17, "1");
		S.DrawString(61, 18, "1");
		S.DrawString(61, 19, "1");
		S.DrawString(61, 20, "1");
		S.DrawString(61, 21, "1");
		S.DrawString(61, 22, "1");
		S.DrawString(57, 22, "111111111");
		break;
	case(2)://makes a 2 out of 2s
		S.DrawString(60, 13, "22");
		S.DrawString(59, 14, "2"); S.DrawString(62, 14, "2");
		S.DrawString(58, 15, "2"); S.DrawString(63, 15, "2");
		S.DrawString(57, 16, "2"); S.DrawString(64, 16, "2");
		S.DrawString(63, 17, "2");
		S.DrawString(62, 18, "2");
		S.DrawString(61, 19, "2");
		S.DrawString(60, 20, "2");
		S.DrawString(59, 21, "2");
		S.DrawString(58, 22, "2222222");
		break;
	case(3)://makes a 3 out of 3s
		S.DrawString(57, 13, "3333333");
		S.DrawString(64, 14, "3");
		S.DrawString(64, 15, "3");
		S.DrawString(64, 16, "3");
		S.DrawString(64, 17, "3");
		S.DrawString(57, 18, "3333333");
		S.DrawString(64, 19, "3");
		S.DrawString(64, 20, "3");
		S.DrawString(64, 21, "3");
		S.DrawString(64, 22, "3");
		S.DrawString(57, 23, "3333333");
		break;
	case(4)://makes a 4 out of 4s
		S.DrawString(56, 14, "4"); S.DrawString(64, 14, "4");
		S.DrawString(56, 15, "4"); S.DrawString(64, 15, "4");
		S.DrawString(56, 16, "4"); S.DrawString(64, 16, "4");
		S.DrawString(56, 17, "4"); S.DrawString(64, 17, "4");
		S.DrawString(57, 18, "44444444");
		S.DrawString(64, 19, "4");
		S.DrawString(64, 20, "4");
		S.DrawString(64, 21, "4");
		S.DrawString(64, 22, "4");
		S.DrawString(64, 23, "4");
		break;
	case(5)://makes a 5 out of 5s
		S.DrawString(57, 13, "5555555");
		S.DrawString(56, 14, "5");
		S.DrawString(56, 15, "5");
		S.DrawString(56, 16, "5");
		S.DrawString(56, 17, "5");
		S.DrawString(57, 18, "5555555");
		S.DrawString(64, 19, "5");
		S.DrawString(64, 20, "5");
		S.DrawString(64, 21, "5");
		S.DrawString(64, 22, "5");
		S.DrawString(57, 23, "5555555");
		break;
	case(6)://makes a 6 out of 6s
		S.DrawString(58, 13, "666666");
		S.DrawString(57, 14, "6"); S.DrawString(64, 14, "6");
		S.DrawString(56, 15, "6");
		S.DrawString(56, 16, "6");
		S.DrawString(56, 17, "6");
		S.DrawString(56, 18, "66666666");
		S.DrawString(56, 19, "6"); S.DrawString(64, 19, "6");
		S.DrawString(56, 20, "6"); S.DrawString(64, 20, "6");
		S.DrawString(56, 21, "6"); S.DrawString(64, 21, "6");
		S.DrawString(56, 22, "6"); S.DrawString(64, 22, "6");
		S.DrawString(57, 23, "6666666");
		break;
	case(7)://make a 7 out of 7s
		S.DrawString(58, 13, "7777777777");
		S.DrawString(66, 14, "7");
		S.DrawString(65, 15, "7");
		S.DrawString(64, 16, "7");
		S.DrawString(63, 17, "7");
		S.DrawString(62, 18, "7");
		S.DrawString(61, 19, "7");
		S.DrawString(60, 20, "7");
		S.DrawString(59, 21, "7");
		S.DrawString(58, 22, "7");
		break;
	case(8)://makes a 8 out of 8s
		S.DrawString(57, 13, "8888888");
		S.DrawString(56, 14, "8"); S.DrawString(64, 14, "8");
		S.DrawString(56, 15, "8"); S.DrawString(64, 15, "8");
		S.DrawString(56, 16, "8"); S.DrawString(64, 16, "8");
		S.DrawString(56, 17, "8"); S.DrawString(64, 17, "8");
		S.DrawString(57, 18, "8888888");
		S.DrawString(56, 19, "8"); S.DrawString(64, 19, "8");
		S.DrawString(56, 20, "8"); S.DrawString(64, 20, "8");
		S.DrawString(56, 21, "8"); S.DrawString(64, 21, "8");
		S.DrawString(56, 22, "8"); S.DrawString(64, 22, "8");
		S.DrawString(57, 23, "8888888");
		break;
	case(9)://makes a 9 out of 9s
		S.DrawString(57, 13, "9999999");
		S.DrawString(56, 14, "9"); S.DrawString(64, 14, "9");
		S.DrawString(56, 15, "9"); S.DrawString(64, 15, "9");
		S.DrawString(56, 16, "9"); S.DrawString(64, 16, "9");
		S.DrawString(56, 17, "9"); S.DrawString(64, 17, "9");
		S.DrawString(57, 18, "9999999");
		S.DrawString(64, 19, "9");
		S.DrawString(64, 20, "9");
		S.DrawString(64, 21, "9");
		S.DrawString(64, 22, "9");
		break;
	}
}

void wheelOfMisfortune::playGame()
{
	display();

	for(int i = 0; i < nbrPlayers; i++)//gives all players 10 points && updates scoreboard
	{
		updateScore(i, 10);
		drawPlayer(i, false);
	}

	bool solved, anotherTurn;
	int playerTurn = 0, spinVal = 0;

	for(int i = 0; i < 10; i++)//game loop, does ten rounds
	{
		//reset vars for each round
		numLtrsUsed = 0;
		vowelsUsed = 0;
		solved = false;
		R.setRange(14,-1);
		string phrase = phrases[R.fnRand()];
		phrase = strupr(&phrase[0]);
		drawPhrase(phrase);

		do//while its still in the round
		{
			do//player turn loop(while its still your turn)
			{
				drawMenu();
				drawPlayer(playerTurn, true);
				anotherTurn = false;
				string input;
				char* solution = new char();
				S.GetStr(42, 10, &input[0], 1, "@");

				switch(input[0])
				{
				case('W'): //spins wheel and asks for a letter
					if(numLtrsUsed <= 26)
					{
						spinVal = spin();
						if(spinVal != 0)
						{
							bool enoughToBuy = true;
							do
							{
								S.DrawString(42, 9, "Enter a letter that isnt taken");
								S.GetStr(42, 10, &input[0], 1, "@");

								if(isVowel(input[0]) && spinVal >= getScore(playerTurn))
								{  
									enoughToBuy = false;
									S.DrawString(42, 8, "Not Enough Money to buy a vowel");
								}
								else
								{  enoughToBuy = true;  }
							}while(isTaken(input[0]) || !enoughToBuy);

							int occurence = 0;
							if(isInPhrase(input[0], phrase, occurence))
							{
								if(isVowel(input[0]))
								{  updateScore(playerTurn, -spinVal);  }
								else
								{  updateScore(playerTurn, spinVal*occurence);  }
								anotherTurn = true;
								fillBlank(input[0], phrase);
							}
							else
							{  updateScore(playerTurn, -spinVal); }
							drawLettersRemaining(input[0]);
							numLtrsUsed +=1;
						}
					}
					else
					{  S.DrawString(42, 9, "No more Letters"); anotherTurn = true; }
					break;
				case('V'): //asks for a vowel

					break;
				case('S')://solve the puzzle
					S.DrawString(2, 21, "Enter the Phrase");
					S.GetStr(2, 22, solution, phrase.size(), "@");
					input = strupr(solution);
					if(checkPhrase(solution, phrase))
					{
						S.DrawString(42, 9, "You win the round!");
						updateScore(playerTurn, 100);
						solved = true;
						lastWinner = playerTurn;
					}
					else
					{ S.DrawString(42, 9, "No, You are wrong"); }
					break;
				default:
					cout <<"\a";
					anotherTurn = true;
					break;
				}
			}while(anotherTurn); //end turn

			drawPlayer(playerTurn, false);
			playerTurn = (playerTurn + 1)%4;
		}while(!solved); //end round
	}//end match
	endGame();
}

bool wheelOfMisfortune::isVowel(char ltr)//checks vowels from most to least commonly used
{  return ltr == 'E' || ltr == 'A' || ltr == 'O' || ltr == 'I' || ltr == 'U';  }

bool wheelOfMisfortune::isInPhrase(char ltr, string phrase, int &occurence)
{
	for(int i = 0; i < phrase.size(); i++)
	{  if(ltr == phrase[i]) occurence++;  }
	return occurence > 0;
}

bool wheelOfMisfortune::isTaken(char ltr)
{
	for(int i = 0; i < 26 && ltrsUsed[i] != NULL; i++)
	{  if(ltr == ltrsUsed[i]) return true;  }
	return false;
}

void wheelOfMisfortune::fillBlank(char ltr, string phrase)
{
	int phraseSize = (int)phrase.size();
	int *locLtr = new int[phraseSize];
	memset(locLtr, 0x00, sizeof(int)*phraseSize);
	int lastLoc = -1;
	int amtInString = 0;

	do
	{
		locLtr[amtInString] = lastLoc = phrase.find(ltr, lastLoc+1);
		amtInString++; //causes amtInString to be 1 higher so we take care of that later
	}while(lastLoc != -1);

	for(int i = 0; i < amtInString - 1; i++)
	{
		int loc = locLtr[i]*2; //gets location for which line its on
		string tmp;
		tmp.clear();//tmp is holding onto values for some reason so I clear it here
		tmp = ltr;

		int sizeLine0 =  blanksInLines[0].size(),
			sizeLine1 =  blanksInLines[1].size() + blanksInLines[0].size(),
			sizeLine2 =  blanksInLines[1].size() + blanksInLines[0].size() + blanksInLines[2].size();

		if(loc < sizeLine0)
		{  S.DrawString(2+loc, 14, &tmp[0]); }
		else if(loc < sizeLine1)
		{
			loc = (loc - sizeLine0);//gets location on this line
			S.DrawString(2+loc, 16, &tmp[0]);
		}
		else if(loc < sizeLine2)
		{
			loc = (loc - sizeLine1);//gets location on this line
			S.DrawString(2+loc, 18, &tmp[0]);
		}
		else
		{
			loc = (loc - sizeLine2);//gets location on this line
			S.DrawString(2+loc, 20, &tmp[0]);
		}
	}
	delete[] locLtr;
}

bool wheelOfMisfortune::checkPhrase(string input, string phrase)
{
	if(input.size() < phrase.size()) return false;
	for(int i = 0; i < input.size(); i++)
	{  if(input[i] != phrase[i]) return false;  }

	return true;
}

void wheelOfMisfortune::loadPhrases()
{
	ifstream infile;
	infile.open("WordsAndPhrases.txt");
	for(int i = 0; !infile.eof() && i < 15; i++)
	{
		getline(infile, phrases[i]);
	}
	infile.close();
}

void wheelOfMisfortune::endGame()
{
	S.Box(20,5, 62, 20, GOLD);
	string winString = "Player";
	winString.append(to_string(lastWinner + 1));
	winString.append(" is the Winner! Play Again?(y/n)");
	S.DrawString(21, 10, &winString[0]);

	string input;
	S.GetStr(winString.size() + 21, 10, &input[0], 1, "@");

	if(input[0] == 'Y')
	{  playGame();  }
}