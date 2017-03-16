#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <dos.h>
#include <windows.h>

using namespace std;


//dimensions of square board to be created
//41 is maximum for fullscreen
//20 is recommended
const int BOARD_DIM = 40;
const char LIVE_CHAR = '@';
const char DEAD_CHAR = '.';
const int MAX_GENERATIONS = 100;


//prints board in console
void print_board( int board[][BOARD_DIM] ) {

	for (int row = 0; row < BOARD_DIM; row++) {		
		for (int column = 0; column < BOARD_DIM; column++) {
			if ( board[row][column] == 1) {
				//print live char	
				cout << " " << LIVE_CHAR ; 
			} else {
				//print dead char
				cout << " " << DEAD_CHAR;
			}
		}
		cout << endl;
	}
}


int update_cell( int board[][BOARD_DIM], int cellRow, int cellColumn ) {

	int liveNeighbors = 0;


	if ( cellRow - 1 >= 0 && cellRow + 1 < BOARD_DIM && cellColumn - 1 >= 0 && cellColumn + 1 < BOARD_DIM ) {
		//loop through 8 neighbors to calculate number alive and dead
		for (int row = cellRow - 1; row <= cellRow + 1; row++){
			for (int col = cellColumn - 1; col <= cellColumn + 1; col++) {
				if ( board[row][col] == 1 ) {
					liveNeighbors++;
				}
			}
		}
	}
	/* } else if (/* top row) {

	} else if (/*bottom row) {

	} else if (/*left side) {

	} else if (/*right side) {

	} else { //corner

	}
	*/


	if ( liveNeighbors < 2 || liveNeighbors > 3) { //if cell has more than 3 live or less than 2 live, it dies
		return 0;
	} else if ( board[cellRow][cellColumn] == 0 && liveNeighbors == 2) { // if cell is dead but has 2 live neighbors, it stays dead
		return 0;
	} else if ( board[cellRow][cellColumn] == 0 && liveNeighbors == 3) { // if cell is dead but has 3 live neighbors, it becomes alive
		return 1;
	} else { // all live cells with 2/3 neighbors live
		return 1;
	}




}



int main() {

	srand(time(NULL));

	int currentGeneration = 0;
	int board[BOARD_DIM][BOARD_DIM];
	int nextBoard[BOARD_DIM][BOARD_DIM];


	//create a pseudorandom start board
	for (int row = 0; row < BOARD_DIM; row++) {
		//iterate row
		for (int column = 0; column < BOARD_DIM; column++) {
			//iterate column
			//set element to 0
			board[row][column] = rand() % 2;
			nextBoard[row][column] = 0;
		}
	}




	//play life
	while (currentGeneration <= MAX_GENERATIONS) {

		//print board to console;
		print_board(board);

		cout << "GENERATION: " << currentGeneration << endl;

		//update board
		for (int row = 0; row < BOARD_DIM; row++ ) {

			for (int column = 0; column < BOARD_DIM; column++) {
				//update the relevant cell of nextBoard[][] based on cell of board[][]
				nextBoard[row][column] = update_cell(board,row,column);

			}
		}

		//replace new board with old board
		for (int row = 0; row < BOARD_DIM; row++ ) {

			for (int col = 0; col < BOARD_DIM; col++) {
				board[row][col] = nextBoard[row][col];
			}
		}

		currentGeneration++;

		sleep(1);

	}




}