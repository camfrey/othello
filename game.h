/*  lab3Header.h
*   Cameron Frey, Liam Jordan - CISC220 Lab 3
*   3/29/2020
*   Functions defined per the requirements of the "CISC220 Lab 3" Document
*/

#include <iostream>             //Pre-processor commands
#include <ostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
using namespace std;

struct GameBoard {
	char **board;  // the othello board
	int size;  //for the size of the board (it's a square, so size is one dimension)
	char p;  //for current player ('X' or 'O')
	int totalct;  // for number of used squares (so that when the board is full, the game stops)
};

int recursiveSort(char arr[], int i, int len);
//uses recursion and the selection sort method to sort a list of characters

int innerLoopSort(char arr[],int j, int m,int len);

void recPrint(char *arr, int len, int index);
//takes an array of characters and prints the array at a starting index recursively

void makeBoard(GameBoard *game, int ct, bool flag); // 10 pts
/* This function recursively makes the board by recursively calling the makeBoard2 function
 * for each row being created.  Once all rows have been created, it sets the middle four squares
 * of the board to 	'X' 'O'
 * 									'O' 'X'
 * (See the printed board output at the end of these instructions for an example)
 * This function takes the game, the current count, and a flag indicating whether
 * this board was already allocated or needs to be allocated for the first time.
 */

 void makeBoardInner(GameBoard *game, int ct, bool flag, int i, int j);

void getSize(int &size);  // 3 pts
/* getSize takes an input parameter by reference.  It randomly finds a size, and then rounds up to the next
* even number.
*/

char ckwin(GameBoard *game);  // 12 pts
/*ckwin()
*This function takes as input the current game object (note: I had this function determine the count of
* the current game object’s player, then switched the game object’s player to the other player, and
* counted the other player’s squares on the board, and compared the two, printing out who won.
*It returns nothing, but prints out who won.
*/

void ckwinCT(GameBoard *game, int *player1, int *player2, int x, int y);
//Helper function for ckwin that counts total pieces for player 1 and 2

void printBoard(GameBoard *game, int ct);  //8 pts
/* this function takes as input the current game piece and the count, indicating which row is being printed out.  It
prints out the board, as seen in the output.
*/

void printBoardHelp(GameBoard *game, int i, int j, bool flag);
// Helper function to printBoard that does the recursive loops

bool compplacepiece(GameBoard *game);  // 20 pts
/*compplacepiece:
This function is used for when the computer is playing as one (or both) of the players.  It determines
the location on the board where, if it places its piece, the most other pieces will be fixed.  It is not
terribly intelligent – it just picks randomly among the squares in which the most pieces will be flipped.
This function takes as an input parameter the GameBoard object game.  This function is not
recursive.  It calls the function findbest spot to find the best x and y location on the board that
will flip the most pieces.  If there are no spots on the board that flip pieces, the function prints
out that the player forfeits their turn and returns false.  Otherwise, it calls figureoutflipping to
flip the legal pieces on the board after placing the game piece at location x y  It returns true if
a piece was placed successfully, and false if there was nowhere to place a piece that would result
in flipping.
*/

int howManyFlips(GameBoard *game, int x, int y);
//Calculates how many pieces would be flipped for a given direction

bool  placepieceperson(GameBoard *game); //20 pts
/* This function is for a human placing a piece on the board.  If the human
chooses a square that is not located on the board, it alerts the human that they
forfeited a turn and returns false.  If the human chooses a square that does not
result in any flipping, it alerts the human that they forfeited a turn and
returns false.  Otherwise it places the piece and flips all possible pieces
in all possible directions
*/

void initBoard(GameBoard *game);
//Places starting pieces in the center of the board

void bestSpot(GameBoard *game, int *bestx, int *besty, int temp, int bestSoFar, int x, int y);
//Helper function for compplacepiece that picks the best spot on the board

int shouldweflip(int x, int y, int xd, int yd, GameBoard *game, int ct);
/*shouldweflip: this function takes as input the current x and y position, the direction, a game object, and the count
* how many pieces might be flipped.  It returns that number.
 */

void flipping(int x, int y, int xd, int yd, GameBoard *game, bool flag);
/* flipping: I used this function when I’d already determined that the direction would indeed result
in pieces being flipped, and thus I only had to worry about flipping pieces in this function */

void playGame(bool fp1,bool fp2,GameBoard *game,bool whoplaysfirstflag);

void startGame(GameBoard *game);
