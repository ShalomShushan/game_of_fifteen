#include "GameOfFifteen.h"

//Simple constructor, setting default values//
GameOfFifteen::GameOfFifteen()
{
	gameOver = false;
	tileX = 0;
	tileY = 0;
	tileNumber = 0;
	dimension = 0;
}

/*  
The search function searches if the selected tile exists in the array (on the board).
If it does it gives us the coordinates of that tile so that other functions can manipulate it.
i - the y axis
n - the x axis 
*/
bool GameOfFifteen::search()
{
	bool isFound = false;

	for(int i = 0; i < dimension; i++)
	{
		for(int n = 0; n < dimension; n++)
		{
			if(board[i][n] == tileNumber) //Found it//
			{
				tileY = i; //Save Y coordinate//
				tileX = n; //Save X coordinate//
				isFound = true;
			}
		}
	}

	return isFound;
}


/*
This function is called after every move the player makes. If the board is sorted the game is over.
If we check the last line then there is a blank space, which is 0 in the actual array, so we need to check the numbers excluding the last 2.
if:

1 2 3 
4 5 6
7 8 

The blank space is actually stored as 0

array 0 =	[1] [2] [3]
array 1 =	[4] [5] [6]
array 2 = 	[7] [8] [0]

Obviously the array is not sorted in this case so we must not compare 8 and 0, that is why I have a special condition in this function
*/
bool GameOfFifteen::isSorted()
{
	bool isSorted = true;

	for(int i = 0; i < dimension; i++)
	{
		for(int n = 0; n < dimension; n++)
		{
			if(n == dimension - 1 && i != dimension - 1) //If we compare 3 and 4, those are not in the same array as shown above//
			{
				if(board[i][n] > board[i + 1][0])
				{
					isSorted = false;
				}
			}
			else if(n == dimension - 2 && i == dimension - 1) //This is the special condition, if this is true we are about to compare 8 and 0 (in the example)//
			{
				break;
			}
			else //Normal comparison between numbers in the same array//
			{
				if(board[i][n] > board[i][n + 1])
				{
					isSorted = false;
				}
			}
		}
	}

	return isSorted;
}


//Just getting the board size the user wants to play. Smallest 3x3, bigest 9x9, 0 to quit//
void GameOfFifteen::getDimensions()
{
	do
	{
		cout << "Enter size (0 to exit): ";
		cin >> dimension;

		if(dimension > 9)
		{
			cout << "Maximum size is 9!" << endl << endl;
		}
		else if(dimension < 3 && dimension != 0)
		{
			cout << "Minimum size is 3!" << endl << endl;
		}

		if(dimension == 0)
		{
			cout << "The game will now quit" << endl;
			exit(1);
		}
	}
	while(dimension > 9 || dimension < 3);

	cout << endl;
}

//A simple function that prints the board. This function is called after every move//
void GameOfFifteen::draw()
{
	//Align the tiles//
	cout << right;

	for(int i = 0; i < dimension; i++)
	{
		for(int n = 0; n < dimension; n++)
		{
			if(board[i][n] == 0) //Zero is the blank spot//
			{
				cout << setw(2) << " " << setw(2) << "";
			}
			else
			{
				cout << setw(2) << board[i][n] << setw(2) << " ";
			}
		}

		cout << endl;
	}

	cout << endl << endl;
}

/*
Creates the array (the game board). If the dimension is even the last 2 digits must be reversed
or this is unsolvable in the way we arrange the board (worse-case shuffle)

15 14 13 12
11 10 09 08
07 06 05 04
03 01 02   -->> the 2 and 1 must be reversed in an even dimension (4x4 in here)
*/
void GameOfFifteen::fillArray()
{
	//Creates the pool of numbers//
	int numbers = (int)pow(dimension,2) - 1;
	bool isEven = false;

	if(dimension % 2 == 0)
	{
		isEven = true;
	}
	//Filling in the array with the numbers according to dimensions, when the numbers hit 0 we stop//
	int n; //I'm using i and n outside the loops, so they are craeted here//
	int i;

	for(i = 0; i < dimension; i++)
	{
		for(n = 0; n < dimension; n++)
		{
			if(isEven)
			{
				if(numbers == 2)
				{
					board[i][n] = numbers - 1;
				}
				else if(numbers == 1)
				{
					board[i][n] = numbers + 1;
				}
				else
				{
					board[i][n] = numbers;
				}
			}
			else
			{
				board[i][n] = numbers;
			}

			numbers--;

			if(numbers == 0)
			{
				break;
			}
		}
	}

	/*
	Creates the empty tile. At this point 'i' is overshooting by 1 due to coming out of the for loop
	and 'n' is one short of the tile due to the break when numbers == 0
	*/
	board[i - 1][n + 1] = 0;
}

/*
The name is misleading. The actual movement is in the check-functions.
Simply calls functions to check if the empty tile is adjecent to the user's selected tile.
If it's possible to move the tile the check function will call the swap function
*/
void GameOfFifteen::moveTile()
{
	if(checkAbove()			//Is the blank spot somewhere adjecent? swap has been made//
		|| checkBelow() 
		|| checkLeft() 
		|| checkRight())
	{
		system("cls"); //Clear the screen and draw it again with the swap in place//
		draw();
		cout << "Tile moved!" << endl;

		if(isSorted()) //Check if that was the winning move//
		{
			gameOver = true;
		}

	}
	else
	{
		system("cls");
		draw();
		cout << "Tile can't be moved" << endl;
	}
}

/* 
All the check-functions are the same. Look up/down/left/right if you spot the blank spot call a swap//
*/
bool GameOfFifteen::checkAbove()
{
	if(tileY == 0)
	{
		return false;
	}

	bool isAbove = false;

	if(board[tileY - 1][tileX] == 0)
	{
		swap(tileY - 1, tileX);
		isAbove = true;
	}

	return isAbove;
}

bool GameOfFifteen::checkBelow()
{
	if(tileY == dimension - 1)
	{
		return false;
	}

	bool isBelow = false;

	if(board[tileY + 1][tileX] == 0)
	{
		swap(tileY + 1, tileX);
		isBelow = true;
	}

	return isBelow;
}

bool GameOfFifteen::checkLeft()
{
	if(tileX == 0)
	{
		return false;
	}

	bool isLeft = false;

	if(board[tileY][tileX - 1] == 0)
	{
		swap(tileY, tileX - 1);
		isLeft = true;
	}

	return isLeft;
}

bool GameOfFifteen::checkRight()
{
	if(tileX == dimension - 1)
	{
		return false;
	}

	bool isRight = false;

	if(board[tileY][tileX + 1] == 0)
	{
		swap(tileY, tileX + 1);
		isRight = true;
	}

	return isRight;
}


/*
Pretty straight forward. Send in the coordinates of the blank tile and I'll swap 
(the tile coordinates are saved in the class private variables, so thoght we use them they are not passed).
*/
void GameOfFifteen::swap(int newY, int newX)
{
	int temp = board[tileY][tileX];
	board[tileY][tileX] = board[newY][newX];
	board[newY][newX] = temp;
}

// The actual game//

void GameOfFifteen::game()
{
	gameOver = false;

	getDimensions();
	fillArray();
	system("cls");
	draw();

	do
	{
		cout << "Choose a tile number to move (0 to stop playing): ";
		cin >> tileNumber;

		if(tileNumber == 0)
		{
			cout << "We're sorry to see you leave :(" << endl << endl;
			exit(2);
		}

		if(tileNumber > pow(dimension, 2) - 1 || tileNumber < 1 || !search())
		{
			system("cls");
			draw();
			cout << "Tile doesn't exist!" << endl;
		}
		else
		{
			moveTile();
		}
	}
	while(tileNumber > pow(dimension, 2) - 1 || tileNumber < 1 || !search() || !gameOver);

	cout << "Well done!" << endl;
}