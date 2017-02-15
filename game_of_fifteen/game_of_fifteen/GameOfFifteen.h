#pragma once

#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

//Maximum board size 9x9 || Minimum board size 3x3//
const int DIM_MAX = 9;
const int DIM_MIN = 3; 

class GameOfFifteen
{
private:
	//Game info//
	bool gameOver;
	//Tile info//
	int tileX,
		tileY,
		tileNumber;
	//Board info//
	//Creates a board at maximum size (even though not all might be used, is there a better way?)//
	int board[DIM_MAX][DIM_MAX];
	int dimension;
public:
	GameOfFifteen();
	void getDimensions();
	void fillArray();
	void draw();
	bool search();
	bool isSorted();
	void moveTile();
	bool checkAbove();
	bool checkBelow();
	bool checkLeft();
	bool checkRight();
	void swap(int newY, int newX);
	void game();
};