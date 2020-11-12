/*  lab3Functions.cpp
*   Cameron Frey, Liam Jordan - CISC220 Lab 3
*   3/29/2020
*   Functions defined per the requirements of the "CISC220 Lab 3" Document
*/

#include "game.h"
#include <iostream>             //Pre-processor commands
#include <ostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>


int innerLoopSort(char arr[],int j, int m,int len) {
	if (j >= len){
		return m;
	}//end if
	else{
		if (arr[j] < arr[m]) {
			m = j;
		}//end if
		return (innerLoopSort(arr,j+1, m,len));
	}//end else
}//end innerLoopSort

int recursiveSort(char arr[], int i, int len){
	if(i >= len){
		return 0;
	} //end if
	else{
		int m = i;
		m=innerLoopSort(arr, i, m, len);
		char tmp = arr[m];
		arr[m] = arr[i];
		arr[i] = tmp;
		return recursiveSort(arr, i+1, len);
	} //end else
}//end recursiveSort

void recPrint(char *arr, int len, int index){
	if(index == len - 1){
		cout << arr[index] << endl;
	}//end if
	else{
		cout << arr[index];
		recPrint(arr, len, index+1);
	}//end else
}//end recPrint

void makeBoard(GameBoard *game, int ct, bool flag){
int i = 0; // denoted for outer for loop replacement (Row)
int j = 0; // denoted for nested for look replacement (Column)
	if(flag==true){ // need to allocate the matrix
		game->board = new char*[game->size]; //creates a row
		makeBoardInner(game,ct,flag,i,j); // Calls helper function to make the columns
																			// with flag==true to let it know it is
																			//making columns but not filling yet
	}
	flag = false; //sets flag to false after matrix is done
	i=j=0; //resets i and j
	makeBoardInner(game,ct,flag,i,j); // calls helper function with flag==false
																		// to fill all rows and columns with '-'
	initBoard(game); // adds X's and O's
}

void initBoard(GameBoard *game){
	game->board[(game->size)/2][(game->size)/2]='X';
	game->board[((game->size)/2)-1][((game->size)/2)-1]='X';
	game->board[((game->size)/2)-1][((game->size)/2)]='O';
	game->board[((game->size)/2)][((game->size)/2)-1]='O';
}

void makeBoardInner(GameBoard *game, int ct, bool flag, int i, int j){
	if(flag==true){
		if(i==game->size){
			return;
		}//end if
		else{
			game->board[i] = new char[game->size];
			i++;
			makeBoardInner(game,ct,flag,i,j);
		}//end else
	}//end if
	else{
			if(i==game->size && j==0){
				return;
			}//end if
			else{
				if(j==game->size && i!=game->size){
					j=0;
					i++;
				}//end if
				else{
					game->board[i][j] = '-';
					j++;
				}//end else
				makeBoardInner(game,ct,flag,i,j);
			}// end else
	}//end else
}//end makeBoardInner

void getSize(int &size){
	size = rand() % 15 + 5;
	if((size % 2) != 0){
		size++;
	}// end if
}//getSize

char ckwin(GameBoard *game){
	int player1, player2;
	player1 = player2 = 0;
	ckwinCT(game,&player1,&player2,0,0);
	cout << player1 << ": Player X score" <<endl;
	cout << player2 << ": Player O score" <<endl;
	if(player1 == player2){
		return 'T';
	}//end if
	else{
		if(player1>player2){
			return 'X';
		}// end if
		else{
			return 'O';
		}//end else
	}//end else
}//end chkwin

void ckwinCT(GameBoard *game, int *player1, int *player2, int x, int y){
	if((x == (game->size - 1)) && (y == (game->size - 1))){
		if(game->board[y][x] == 'X'){
			*player1=*player1+1;
		}//end if
		else if(game->board[y][x] == 'O'){
			*player2=*player2+1;
		}//end else if
		return;
	}//end if
	else if(x == game->size){
		x = 0;
		y++;
		ckwinCT(game,player1,player2,x,y);
	}//end else if
	else{
		if(game->board[y][x] == 'X'){
			*player1=*player1+1;
		}// end if
		else if(game->board[y][x] == 'O'){
			*player2=*player2+1;
		}//end else if
		ckwinCT(game,player1,player2,x+1,y);
	}//end else
}//end ckwinCT


void printBoard(GameBoard *game, int ct){
	cout<<' '<< '\t';
	int i = 0;
	int j = 0;
	bool flag = true;
	printBoardHelp(game,i,j,flag);
	cout<<endl;
	i=j=0;
	flag = false;
	printBoardHelp(game,i,j,flag);
	return;
}//end printBoard

void printBoardHelp(GameBoard *game, int i, int j, bool flag){
	if(flag==true){
		if(i==game->size){
			return;
		}
		else{
			cout << i << '\t';
			i++;
			printBoardHelp(game,i,j,flag);
		}
	}
	else{
		if(i==game->size && j==0){
			return;
		}//end if
		else{
			if(j==game->size+1 && i!=game->size){
				j=0;
				i++;
				cout << endl;
			}//end if
			else{
				if(j==0){
					cout << i << '\t';
					j++;
				}
				else{
					cout << game->board[i][j-1] << '\t';
					j++;
				}
			}//end else
			printBoardHelp(game,i,j,flag);
		}// end else
	}//end else
}//end printBoardHelp



bool placepieceperson(GameBoard *game){
	bool flag = false;
	int x,y;
	int ct = 0;
	x=y=0;
	cout << "Player: " << game->p << " Pick a X coordinate: ";
	cin >> x;
	cout << endl;
	cout << "Player: " << game->p << " Pick a Y coordinate: ";
	cin >> y;
	cout << endl;
	if((x < 0) || (y < 0) || (y >= game->size) || (x >= game->size)){
		return false;
	}
	if(shouldweflip(x,y,0,1,game,ct)!=0){
		flag = true;
		flipping(x,y,0,1,game,false);
	}
	if(shouldweflip(x,y,0,-1,game,ct)!=0){
		flag = true;
		flipping(x,y,0,-1,game,false);
	}
	if(shouldweflip(x,y,1,0,game,ct)!=0){
		flag = true;
		flipping(x,y,1,0,game,false);
	}
	if(shouldweflip(x,y,-1,0,game,ct)!=0){
		flag = true;
		flipping(x,y,-1,0,game,false);
	}
	if(shouldweflip(x,y,1,1,game,ct)!=0){
		flag = true;
		flipping(x,y,1,1,game,false);
	}
	if(shouldweflip(x,y,-1,-1,game,ct)!=0){
		flag = true;
		flipping(x,y,-1,-1,game,false);
	}
	if(shouldweflip(x,y,1,-1,game,ct)!=0){
		flag = true;
		flipping(x,y,1,-1,game,false);
	}
	if(shouldweflip(x,y,-1,1,game,ct)!=0){
		flag = true;
		flipping(x,y,-1,1,game,false);
	}
	if(flag==true){
		game->board[y][x]=game->p;
		game->totalct+=1;
	}
	return flag;
}//end placepieceperson

int shouldweflip(int x, int y, int xd, int yd, GameBoard *game, int ct){
	if((x==0 && xd==-1) || (y==0 && yd==-1) || (y==game->size-1 && yd==1) || (x==game->size-1 && xd==1)){
			return 0;
	}// end if
	else{
			if((game->board[y+yd][x+xd] != game->p) && (game->board[y+yd][x+xd] != '-')){
				ct++;
				shouldweflip(x+xd,y+yd,xd,yd,game,ct);
			}//end if
			else if(game->board[y+yd][x+xd] == '-'){
				ct = 0;
				return ct;
			}// end else if
			else{
				return ct;
			}//end else
		}//end else
	//return ct; Leaving this "Dummy return case" commented leads to a warning
	// but uncommenting it results in the game not working
}// end shouldweflip

void flipping(int x, int y, int xd, int yd, GameBoard *game, bool flag){
	if(flag==false){
		x+=xd;
		y+=yd;
		flag = true;
	}//end if
	else if(game->board[y][x] != game->p){
		game->board[y][x] = game->p;
		x+=xd;
		y+=yd;
	}//end else if
	else{
		return;
	}//end else
	flipping(x,y,xd,yd,game,flag);
}//end flipping

bool compplacepiece(GameBoard *game){
	int bestx = 0;
	int besty = 0;
	bestSpot(game, &bestx, &besty, 0, 0, 0, 0);
	bool flag = false;
	int ct = 0;
	cout << "Player: " << game->p << " placing (" << bestx  <<" , "<< besty << ")"<< endl;
	if(shouldweflip(bestx,besty,0,1,game,ct)!=0){
		flag = true;
		flipping(bestx,besty,0,1,game,false);
	}
	if(shouldweflip(bestx,besty,0,-1,game,ct)!=0){
		flag = true;
		flipping(bestx,besty,0,-1,game,false);
	}
	if(shouldweflip(bestx,besty,1,0,game,ct)!=0){
		flag = true;
		flipping(bestx,besty,1,0,game,false);
	}
	if(shouldweflip(bestx,besty,-1,0,game,ct)!=0){
		flag = true;
		flipping(bestx,besty,-1,0,game,false);
	}
	if(shouldweflip(bestx,besty,1,1,game,ct)!=0){
		flag = true;
		flipping(bestx,besty,1,1,game,false);
	}
	if(shouldweflip(bestx,besty,-1,-1,game,ct)!=0){
		flag = true;
		flipping(bestx,besty,-1,-1,game,false);
	}
	if(shouldweflip(bestx,besty,1,-1,game,ct)!=0){
		flag = true;
		flipping(bestx,besty,1,-1,game,false);
	}
	if(shouldweflip(bestx,besty,-1,1,game,ct)!=0){
		flag = true;
		flipping(bestx,besty,-1,1,game,false);
	}
	if(flag==true){
		game->board[besty][bestx]=game->p;
		game->totalct+=1;
	}
	return flag;
}//end compplacepiece

void bestSpot(GameBoard *game, int *bestx, int *besty, int temp, int bestSoFar, int x, int y){
	if(y==game->size && x==0){
		return;
	}//end if
	else if(x==game->size){
			x=0;
			y++;
			bestSpot(game, bestx, besty, temp, bestSoFar, x, y);
	}//end else if
	else if(game->board[y][x]=='-'){
		temp = howManyFlips(game,x,y);
		if(temp>bestSoFar){
			*bestx = x;
			*besty = y;
			bestSoFar = temp;
		}//end if
		x++;
		bestSpot(game, bestx, besty, temp, bestSoFar, x, y);
	}//end else if
	else{
		x++;
		bestSpot(game, bestx, besty, temp, bestSoFar, x, y);
	}//end else
}//end best spot

int howManyFlips(GameBoard *game, int x, int y){
	int ct = 0;
	int flips = 0;
	flips+=shouldweflip(x,y,0,1,game,ct);
	flips+=shouldweflip(x,y,0,-1,game,ct);
	flips+=shouldweflip(x,y,1,0,game,ct);
	flips+=shouldweflip(x,y,-1,0,game,ct);
	flips+=shouldweflip(x,y,1,1,game,ct);
	flips+=shouldweflip(x,y,-1,-1,game,ct);
	flips+=shouldweflip(x,y,1,-1,game,ct);
	flips+=shouldweflip(x,y,-1,1,game,ct);
	return flips;
}//end howManyFlips

void playGame(bool fp1,bool fp2,GameBoard *game,bool whoplaysfirstflag) {
	bool s1 = true;
	bool s2 = true;
	if (fp1 && fp2 && (s1 || s2)) {
		if (whoplaysfirstflag) {
				game->p = 'X';
				s1 = placepieceperson(game);
				printBoard(game,0);
				game->p = 'O';
				s2 = placepieceperson(game);
				printBoard(game,0);
		}
		else {
			game->p = 'O';
			s1 = placepieceperson(game);
			printBoard(game,0);
			game->p = 'X';
			s2 = placepieceperson(game);
			printBoard(game,0);
		}
	}
	else if (fp1 == false && fp2 == false && (s1 || s2)) {
		game->p = 'X';
		s1 = compplacepiece(game);
		printBoard(game,0);
		game->p = 'O';
		s2 = compplacepiece(game);
		printBoard(game,0);
	}
	else {
		if (whoplaysfirstflag) {
				game->p = 'X';
				s1 = placepieceperson(game);
				printBoard(game,0);
				game->p = 'O';
				s2 = compplacepiece(game);
				printBoard(game,0);
		}
		else {
			game->p = 'X';
			s1 = compplacepiece(game);
			printBoard(game,0);
			game->p = 'O';
			s2 = placepieceperson(game);
			printBoard(game,0);
		}
	}
	if (s1 == false && s2 == false || game->totalct == game->size * game->size) {
		cout << "Game over" << endl;
		printBoard(game,0);
		return;
	}
	playGame(fp1,fp2,game,whoplaysfirstflag);
}

void startGame(GameBoard *game) {
	cout << "How many players? (0,1, or 2)" << endl;
	int numplayers;
	cin >> numplayers;
	if (numplayers == 0) {
		playGame(false,false,game, true);
	}
	else if (numplayers == 1) {
		bool whoplaysfirstflag;
		rand()%2 == 0? whoplaysfirstflag = true:whoplaysfirstflag = false;
		playGame(true,false,game,whoplaysfirstflag);
	}
	else playGame(true,true,game,true);
	char w = ckwin(game);
	if (w != 'T') {
		cout << w << " WON!!!!  " << endl;
	}
	else {
		cout << "Tie game. " << endl;
	}
	string s;
	cout << "Play again? (Y or N)" << endl;
	cin >> s;
	if (s == "Y") {
		game->totalct = 4;
		makeBoard(game,0, false);
		cout << "STARTING OVER" << endl;
		printBoard(game,0);
		startGame(game);
	}
	else {
		cout << "THANKS FOR PLAYING!" << endl;
	}
}
