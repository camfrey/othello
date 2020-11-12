/*  lab3Main.cpp
*   Cameron Frey, Liam Jordan - CISC220 Lab 3
*   3/29/2020
*   Functions defined per the requirements of the "CISC220 Lab 3" Document
*/

#include "game.h"
using namespace std;

int main() {
	srand(time(NULL));
	int size = 0;
	getSize(size);  // gets the size for the game board.  Note we only do this once for this game.
	GameBoard *game = new GameBoard;  // places a gameBoard struct object on the heap.
	game->size = size;  //sets the gameboard's size
	game->totalct = 4;  // the 4 middle squares are taken
	cout << "Size is " << game->size << endl;
	makeBoard(game,0,true);
	printBoard(game, 0);  // for testing purposes

	startGame(game);

	//Recursive sort tests
	char arr[6] = {'f','e','d','c','b','a'};
	recPrint(arr,6,0);
	recursiveSort(arr,0,6);
	recPrint(arr,6,0);
}
