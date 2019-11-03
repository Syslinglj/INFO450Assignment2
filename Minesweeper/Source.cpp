#include <iostream>
#include <time.h>
using namespace std;

const int CSIZE = 8;
const int RSIZE = 8;
void displayBoard(int gameBoard[RSIZE][CSIZE]);
void askLocation(int& Locx, int& Locy);
void randLocation(int& spot);

int main()
{
	int guessx = 0, guessy = 0, bombx = 1, bomby = 2;
	int gold[5][2] = { { 1,6}, { 0,2}, { 6,6}, { 7,2}, { 6,5} };
	int game[RSIZE][CSIZE] = { {5,5,5,5,5,5,5,5},{5,5,5,5,5,5,5,5},{5,5,5,5,5,5,5,5},{5,5,5,5,5,5,5,5},{5,5,5,5,5,5,5,5},{5,5,5,5,5,5,5,5},{5,5,5,5,5,5,5,5},{5,5,5,5,5,5,5,5} };
	int attempt = 1, score = 0, remaining = 5;
	bool cont = true;
	char input = 'Y';
	while (cont == true)
	{
		for (int r = 0; r < 5; r++) //randomly assigns gold/bomb location
		{
				randLocation(gold[r][0]);
				randLocation(gold[r][1]);
		}
		//randLocation(bombx);
		//randLocation(bomby);

		for (int r = 0; r < 5; r++) //states gold/bomb locations for testing
		{
			cout << "Gold #" << r + 1 << " X:" << gold[r][0] << " Y:" << gold[r][1] << endl;
		}
		cout << "Bomb" << " X:" << bombx << " Y:" << bomby << endl;

		//displays board blank board to start
		displayBoard(game);
		cout << "******************************" << endl;
		cout << "****  You have 5 Guesses  ****" << endl;
		cout << "****    To Find 5 Gold    ****" << endl;
		cout << "****   Beware of 1 Bomb   ****" << endl;
		cout << "****      Good Luck       ****" << endl;
		cout << "******************************" << endl;
		// clears ? from board
		for (int r = 0; r < 8; r++)
		{
			for (int c = 0; c < 8; c++)
			{
				game[r][c] = 0;
			}
		}

		// adds gold/bomb to gameboard
		for (int r = 0; r < 5; r++)
		{
			game[gold[r][0]][gold[r][1]] = 1;
		}
		game[bombx][bomby] = 2;
		// asks for 5 guesses

		for (int k = 0; k < 5; k++)
		{

			guessx = 0, guessy = 0;
			askLocation(guessx, guessy);
			cout << "Guess # " << attempt << ": ";
			remaining--;
			// guess was a miss
			if (game[guessx][guessy] == 0)
			{
				cout << "Oh no! You missed!" << endl;
				game[guessx][guessy] = 4;
			}
			// guess was a gold hit'
			if (game[guessx][guessy] == 1)
			{
				cout << "You hit the gold!" << endl;
				game[guessx][guessy] = 3;
				k--;
				score++;
				remaining++;
			}
			// guess was a bomb hit
			if (game[guessx][guessy] == 2)
			{
				cout << "Oh no! You hit the bomb! Game Over!" << endl;
				k = 5;
				remaining = 0;
			}
			cout << "You have " << remaining << " guesses left." << endl;
			attempt++;
		}
		displayBoard(game);
		cout << "Your score was " << score << endl;
		cout << "Would you like to go again Y:N" << endl;
		cin >> input;
		if (input == 'Y' || input == 'y')
			cont = true;
		else
			cont = false;
		system("cls");
	}
}

// displays the game board
void displayBoard(int gameBoard[RSIZE][CSIZE]) 
{
	cout << "     1 2 3 4 5 6 7 8 " << endl;
	cout << "     _______________ " << endl;
	for (int row = 0; row < RSIZE; row++)
	{
		cout << row+1 << "   |";
		for (int col = 0; col < CSIZE; col++)
		{
			if (gameBoard[row][col] == 0)
				cout << "  ";
			else if (gameBoard[row][col] == 1)
				cout << "G ";
			else if (gameBoard[row][col] == 2)
				cout << "B ";
			else if (gameBoard[row][col] == 3)
				cout << "F ";
			else if (gameBoard[row][col] == 4)
				cout << "M ";
			else if (gameBoard[row][col] == 5)
				cout << "? ";
		}
		cout << " " << endl;
	}
	cout << "    |_______________ " << endl;
}

//asks the participant for coordinates
void askLocation(int& Locx, int& Locy)  
{
	Locx = 0;
	Locy = 0;
	while (Locx < 1 || Locx > 8)
	{
		cout << "Enter a X-coordinate between 1-8: ";

		cin >> Locx;
		cout << endl;
	}
	while (Locy < 1 || Locy > 8)
	{
		cout << "Enter a Y-coordinate between 1-8: ";
		cin >> Locy;
		cout << endl;
	}
	Locx -= 1;
	Locy -= 1;
}

//generates random x and y for golds and bomb
void randLocation(int& spot)
{
	srand(time(NULL));
	spot = (rand() % 8) + 1;
}

//checks board for points and bombs
