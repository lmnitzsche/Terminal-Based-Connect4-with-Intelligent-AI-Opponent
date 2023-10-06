//Connect 4 Game & Artificial Intelligence
//Created by Logan Nitzsche

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include "stdbool.h"
using namespace std;


struct player
{
	string playerName;
	char playerID;
};

int aiDecision(char board[][10], player activePlayer, int dropChoice);
int playerDecision(char board[][10], player activePlayer, int& dropChoice);
void placeDisc(char board[][10], player activePlayer, int dropChoice);
void displayBoard(char board[][10], player activePlayer);
int checkForWin(char board[][10], player activePlayer);
int checkForSpace(char board[][10]);
void playerWin(player activePlayer);
int restart(char board[][10]);

int main()
{
	player playerOne;
	player playerTwo;
	char board[9][10]; 
	int width = 7; 
	int length = 6; 
	int dropChoice = 0;
	string gameAnswer;
	bool win = false;
	int space = 0;
	int playAgain = 1;
	
	system("clear");

	cout << "Please enter your name: ";
	cin  >> playerOne.playerName;
	cout << endl << "Do you know how to play Connect 4 " << playerOne.playerName << "? ";
	cin >> gameAnswer;

	//Explains rules if the player doesn't know how to play
	if(gameAnswer == "no" || gameAnswer == "n" || gameAnswer == "N" || gameAnswer == "No" || 
	   gameAnswer == "NO" || gameAnswer == "nope" || gameAnswer == "na")
	{
		system("clear");
		cout << endl << "Connect Four is played by two people.";
		sleep(3);
		cout << endl << endl << "The game is played on a vertical board with seven columns and six rows.";
		sleep(3);
		cout << endl << endl << "Each player takes turns dropping one of their colored discs into any column on the board.";
		sleep(3);
		cout << endl << endl << "The disc drops to the lowest available slot in the column.";
		sleep(3);
		cout << endl << endl << "The first person to get four of their discs alligned in a row is the winner!";
		sleep(3);
		cout << endl << endl << "You can win horizontally, veritcally, and diagnally.";
		sleep(3);
		cout << endl << endl << "Good luck " << playerOne.playerName << "!";
		sleep(3);
		cout << endl;
	}
	
	cout << endl << "It's time to play Connect 4!" << endl << endl;
	sleep(4);
	system("clear");

	playerOne.playerID = 'X';
	playerTwo.playerName = "Light Yagami";
	playerTwo.playerID = 'O';

	displayBoard(board, playerOne);
	
	//Runs gameloop
	while(playAgain != 2)
	{
		cout << endl;
		dropChoice = playerDecision(board, playerOne, dropChoice);
		placeDisc(board, playerOne, dropChoice);
		system("clear");
		displayBoard(board, playerOne);
		sleep(4);
		win = checkForWin(board, playerOne);

		if(win == true)
		{
			playerWin(playerOne);
			playAgain = restart(board);
			if(playAgain == false)
			{
				break;
			}
		}

		cout << endl;
		dropChoice = aiDecision(board, playerTwo, dropChoice);
		placeDisc(board, playerTwo, dropChoice);
		system("clear");
		displayBoard(board, playerTwo);
		sleep(4);
		system("clear");
		displayBoard(board, playerOne);
		win = checkForWin(board, playerTwo);

		if(win)
		{
			playerWin(playerTwo);
			playAgain = restart(board);
			if(playAgain == 2)
			{
				break;
			}
		}

		space = checkForSpace(board);

	//Calls for a draw if the board is full
		if(space == 7)
		{
			cout << "The board is full, it is a draw!" << endl;
			playAgain = restart(board);
		}
	}
return 0;
}

//Determines where the user wants to place disc
int playerDecision(char board[][10], player activePlayer, int& dropChoice)
{
	do
	{
		cout << activePlayer.playerName << "'s Turn " << endl;
		cout << "Enter a number between 1 and 7: ";
		cin  >> dropChoice;
		cout << endl;
		while(board[1][dropChoice] == 'X' || board[1][dropChoice] == 'O')
		{
			cout << "That row is full; please enter a new row: ";
			cin  >> dropChoice;
		}
		return dropChoice;

	}while(dropChoice < 1 || dropChoice > 7);
}

//Determines where the AI wants to place disc
int aiDecision(char board[][10], player activePlayer, int dropChoice)
{
		//Searches for Horizontal and Verticle Potential Wins and Blocks
		for(int i = 10; i >= 1; --i)
		{
			for(int j = 10; j >= 1; --j)
			{
				if(board[i][j-1] == 'X' &&
				board[i][j-2] == 'X' &&
				board[i][j-3] == 'X' &&
				board[i][j] != 'O' && 
				(board[i+1][j] == 'X' || board[i+1][j] == 'O') &&
				j <= 7 && j >= 1)
				{
					return j;
				}
				else if(board[i][j-1] == 'O' &&
				board[i][j-2] == 'O' &&
				board[i][j-3] == 'O' &&
				board[i][j] != 'X' && 
				(board[i+1][j] == 'X' || board[i+1][j] == 'O') &&
				j <= 7 && j >= 1)
				{
					return j;
				}
				else if(board[i][j-1] == 'X' &&
				board[i][j-2] == 'X' &&
				board[i][j-3] == 'X' &&
				board[i][j-4] != 'O' && 
				(board[i+1][j-4] == 'X' || board[i+1][j-4] == 'O') &&
				(j-4) <= 7 && (j-4) >= 1)
				{
					return j - 4;
				}
				else if(board[i][j-1] == 'O' &&
				board[i][j-2] == 'O' &&
				board[i][j-3] == 'O' &&
				board[i][j-4] != 'X' && 
				(board[i+1][j-4] == 'X' || board[i+1][j-4] == 'O') &&
				(j-4) <= 7 && (j-4) >= 1)
				{
					return j - 4;
				}
				else if(board[i-1][j] == 'X' &&
				board[i-2][j] == 'X' &&
				board[i-3][j] == 'X' &&
				board[i-4][j] != 'O' &&
				j <= 7 && j >= 1)
				{
					return j;
				}
				else if(board[i-1][j] == 'O' &&
				board[i-2][j] == 'O' &&
				board[i-3][j] == 'O' &&
				board[i-4][j] != 'X' &&
				j <= 7 && j >= 1)
				{
					return j;
				}
			}
		}

		//Searches for Diagnal Potential Wins and Blocks
		for(int i = 10; i >= 1; --i)
		{
			for(int j = 10; j >= 1; --j)
			{
				if(board[i+1][j-1] == 'X' &&
				board[i][j] == 'X' &&
				board[i-1][j+1] == 'X' &&
				board[i-2][j+2] != 'O' && 
				(board[i-1][j+2] == 'X' || board[i-1][j+2] == 'O') &&
				j <= 7 && j >= 1)
				{
					return j + 2;
				}
				else if(board[i+1][j-1] == 'O' &&
				board[i][j] == 'O' &&
				board[i-1][j+1] == 'O' &&
				board[i-2][j+2] != 'X' && 
				(board[i-1][j+2] == 'X' || board[i-1][j+2] == 'O') &&
				j <= 7 && j >= 1)
				{
					return j + 2;
				}
				else if(board[i+1][j-1] == 'X' &&
				board[i][j] == 'X' &&
				board[i-1][j+1] == 'X' &&
				(board[i+2][j-2] != 'X' || board[i+2][j-2] != 'O') &&
				j <= 7 && j >= 1)
				{
					return j - 2;
				}
				else if(board[i+1][j-1] == 'O' &&
				board[i][j] == 'O' &&
				board[i-1][j+1] == 'O' &&
				(board[i+2][j-2] != 'O' || board[i+2][j-2] != 'X') &&
				j <= 7 && j >= 1)
				{
					return j - 2;
				}
				else if(board[i-2][j-2] == 'X' &&
				board[i-1][j-1] == 'X' &&
				board[i][j] == 'X' &&
				board[i+1][j+1] != 'O' && 
				(board[i+2][j+1] == 'X' || board[i+2][j+1] == 'O') &&
				j <= 7 && j >= 1)
				{
					return j + 1;
				}
				else if(board[i-2][j-2] == 'O' &&
				board[i-1][j-1] == 'O' &&
				board[i][j] == 'O' &&
				board[i+1][j+1] != 'X' && 
				(board[i+2][j+1] == 'X' || board[i+2][j+1] == 'O') &&
				j <= 7 && j >= 1)
				{
					return j + 1;
				}

				else if(board[i-2][j-2] == 'X' &&
				board[i-1][j-1] == 'X' &&
				board[i][j] == 'X' &&
				board[i-3][j-3] != 'O' && 
				(board[i-2][j-3] == 'X' || board[i-2][j-3] == 'O') &&
				j <= 7 && j >= 1)
				{
					return j - 3;
				}
				else if(board[i-2][j-2] == 'O' &&
				board[i-1][j-1] == 'O' &&
				board[i][j] == 'O' &&
				board[i-3][j-3] != 'X' && 
				(board[i-2][j-3] == 'X' || board[i-2][j-3] == 'O') &&
				j <= 7 && j >= 1)
				{
					return j - 3;
				}
			}
		}

		//Searches Common Positions for Best Move
		if(board[6][4] == 'X' && board[6][3] == 'X' && board[6][5] != 'O')
		{
			return 5;
		}
		else if(board[6][4] == 'X' && board[6][5] == 'X' && board[6][6] == 'X' && board[6][7] != 'O')
		{
			return 7;
		}
		else if(board[6][2] == 'X' && board[6][4] == 'X' && board[6][3] != 'O' && board[6][3] != 'X')
		{
			return 3;
		}
		else if(board[6][4] == 'X' && board[6][6] == 'X' && board[6][5] != 'O')
		{
			return 5;
		}
		else if(board[6][4] == 'X' && board[6][5] == 'X' && board[6][6] == 'X' && board[6][7] != 'O')
		{
			return 7;
		}
		else if(board[6][4] == 'X' && board[6][5] == 'X' && board[6][7] == 'X' && board[6][6] != 'O')
		{
			return 6;
		}
		else if(board[6][4] == 'X' && board[6][3] == 'X' && board[6][2] == 'X' && board[6][1] != 'O')
		{
			return 1;
		}
		else if(board[6][4] == 'X' && board[6][3] == 'X' && board[6][1] == 'X' && board[6][2] != 'O')
		{
			return 2;
		}
		else if(board[6][4] == 'X' && board[6][5] == 'X' && board[6][3] != 'O')
		{
			return 3;
		}
		else if(board[6][3] == 'X' && board[5][3] == 'X' && board[4][3] != 'O' && board[1][3] != 'X' && board[1][3] != 'O')
		{
			return 3;
		}
		else if(board[6][5] == 'X' && board[5][5] == 'X' && board[4][5] != 'O' && board[1][5] != 'X' && board[1][5] != 'O')
		{
			return 5;
		}
		else if(board[3][4] == 'O' && board[4][3] == 'O' && board[6][1] != 'O' && board[6][1] != 'X' && board[5][2] != 'X' && board[1][1] != 'X' && board[1][1] != 'O')
		{
			return 1;
		}
		else if(board[3][4] == 'O' && board[4][5] == 'O' && board[6][7] != 'O' && board[6][7] != 'X' && board[5][6] != 'X'&& board[1][7] != 'X' && board[1][7] != 'O')
		{
			return 7;
		}
		else if(board[3][4] == 'O' && board[4][3] == 'O' && board[6][1] == 'O' && (board[6][2] == 'X' || board[6][2] == 'O') && board[5][2] != 'X' && board[1][2] != 'X' && board[1][2] != 'O')
		{
			return 2;
		}
		else if(board[3][4] == 'O' && board[4][3] == 'O' && board[5][2] == 'O' && board[6][1] != 'X' && board[1][1] != 'X' && board[1][1] != 'O')
		{
			return 1;
		}
		else if(board[3][4] == 'O' && board[4][5] == 'O' && board[5][6] == 'O' && board[6][7] != 'X' && board[1][7] != 'X' && board[1][7] != 'O')
		{
			return 7;
		}
		else if(board[3][4] == 'O' && board[4][5] == 'O' && board[6][7] == 'O' && (board[6][6] == 'X' || board[6][6] == 'O') && board[5][6] != 'X' && board[1][6] != 'X' && board[1][6] != 'O')
		{
			return 6;
		}
		else if(board[6][6] == 'X' && board[6][5] == 'X' && board[6][4] != 'O')
		{
			return 4;
		}
		else if(board[6][6] == 'X' && board[6][5] == 'X' && board[6][7] != 'O')
		{
			return 7;
		}
		else if(board[6][2] == 'X' && board[6][3] == 'X' && board[6][4] != 'O')
		{
			return 4;
		}
		else if(board[6][2] == 'X' && board[6][3] == 'X' && board[6][1] != 'O')
		{
			return 1;
		}
		else if(board[6][1] == 'X' && board[6][2] == 'X' && board[6][3] != 'O')
		{
			return 3;
		}
		else if(board[6][4] == 'X' && board[6][6] == 'X' && board[6][5] != 'O')
		{
			return 5;
		}
		else if(board[6][4] == 'X' && board[6][2] == 'X' && board[6][3] != 'O')
		{
			return 3;
		}
		else if(board[6][6] == 'X' && board[6][7] == 'X' && board[6][5] != 'O')
		{
			return 5;
		}
		else if(board[6][2] == 'X' && board[5][3] == 'X' && (board[5][4] == 'X' || board[5][4] == 'O') && board[4][4] != 'X' && board[1][4] != 'X' && board[1][4] != 'O')
		{
			return 4;
		}
		else if(board[6][5] == 'X' && board[5][4] == 'X' && (board[5][3] == 'X' || board[5][3] == 'O') && board[4][3] != 'X'&& board[1][3] != 'X' && board[1][3] != 'O')
		{
			return 3;
		}

		//Targets Middle Column
		else if(board[1][4] != 'X' && board[1][4] != 'O')
		{
			return 4;
		}

		//Targets Column of Opponent's Last Disc
		else if(board[1][dropChoice] != 'X' || board[1][dropChoice] != 'O')
		{
			return dropChoice;
		}

		//Targets Columns 3 & 5
		else if(board[1][3] != 'X' || board[1][3] != 'O')
		{
			return 3;
		}
		else if(board[1][5] != 'X' || board[1][5] != 'O')
		{
			return 5;
		}

		//Searches for Legal Move
		else
		{
			for(int i = 1; i <= 7; i++)
			{
				if(board[1][i] != 'X' && board[1][i] != 'O')
				{
					return i;
				}
			}
		}
}
			

//Function to place discs on the board
void placeDisc(char board[][10], player activePlayer, int dropChoice)
{
	int length = 6;
	bool completedTurn = false;

	while(completedTurn != true) 
	{
		if(board[length][dropChoice] != 'X' && board[length][dropChoice] != 'O')
		{
			board[length][dropChoice] = activePlayer.playerID;
			completedTurn = true;
		}
		else
		{
			--length;
		}
	}
}

//Function to display game board
void displayBoard(char board[][10], player activePlayer)
{
	int rows = 6, columns = 7;

	cout << "  1   2   3   4   5   6   7  " << endl 
		 << "-----------------------------" << endl;

	for(int i = 1; i <= rows; i++)
	{
		cout << "| ";
		for(int j = 1; j <= columns; j++)
		{
			if(board[i][j] != 'X' && board[i][j] != 'O')
			{
				board[i][j] = ' ';
			}
			cout << board[i][j] << " | ";
		}
		cout << endl;
	}

	//Confirms that it's the AI's turn
	if(activePlayer.playerName == "Light Yagami")
	{
		cout << endl << activePlayer.playerName << "'s Turn" << endl;
	}
}

//Searches the board for a win
int checkForWin(char board[][10], player activePlayer)
{
	char gameDisc;
	bool win = false;
	gameDisc = activePlayer.playerID;

	for(int i = 8; i >= 1; --i)
	{
		for(int j = 9; j >= 1; --j)
		{
			if(board[i][j] == gameDisc     &&
				board[i-1][j-1] == gameDisc &&
				board[i-2][j-2] == gameDisc &&
				board[i-3][j-3] == gameDisc)
			{
				win = true;
			}
			if(board[i][j] == gameDisc   &&
				board[i][j-1] == gameDisc &&
				board[i][j-2] == gameDisc &&
				board[i][j-3] == gameDisc)
			{
				win = true;
			}
			if(board[i][j] == gameDisc   &&
				board[i-1][j] == gameDisc &&
				board[i-2][j] == gameDisc &&
				board[i-3][j] == gameDisc)
			{	
				win = true;
			}
			if(board[i][j] == gameDisc     &&
				board[i-1][j+1] == gameDisc &&
				board[i-2][j+2] == gameDisc &&
				board[i-3][j+3] == gameDisc)
			{
				win = true;
			}
			if(board[i][j] == gameDisc   &&
				 board[i][j+1] == gameDisc &&
				 board[i][j+2] == gameDisc &&
				 board[i][j+3] == gameDisc)
			{
				win = true;
			}
		}
	}
	return win;
}

//Checks to see if the row you're trying to drop a disc in is full
int checkForSpace(char board[][10])
{
	int space = 0;

	for(int i = 1; i <= 7; ++i)
	{
		if(board[1][i] != ' ')
		{
			++space;
		}
	}
return space;
}

//Announces Winner
void playerWin(player activePlayer)
{
	cout << endl << activePlayer.playerName << " Wins!" << endl;
}

//Prompts user to exit or restart game
int restart(char board[][10])
{
	int initiateRestart = 2;
	string restartAnswer;
	cout << "Would you like to restart?";
	cin  >> restartAnswer;
	if(restartAnswer == "yes" || restartAnswer == "yeah" || restartAnswer == "y" || restartAnswer == "Y" || 
	   restartAnswer == "Yes" || restartAnswer == "Yeah" || restartAnswer == "yep" || restartAnswer == "yup" ||
	   restartAnswer == "Yep" || restartAnswer == "Yup" || restartAnswer == "1")
	{
		for(int i = 1; i <= 6; i++)
		{
			for(int j = 1; j <= 7; j++)
			{
				board[i][j] = ' ';
			}
		}
		initiateRestart == 1;
	}
	return initiateRestart;
}