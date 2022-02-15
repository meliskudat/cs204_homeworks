#ifndef BOARD_H
#define BOARD_H
#include <string >
#include <iostream>

using namespace std;


template < class ItemType >
class Board
{

 public :
	Board() ; // constructor
	Board( int row , int col ) ; // constructor
	~Board() ; // destructor
	void readBoardFromFile ( ifstream & file ) ; // reads file
	void closeCard ( int row , int col ) ; // closes cards
	void CardOpen ( int row , int col ) ; // opens card
	void displayBoard() ; // displays board
	int getRow() ; // gets row
	int getColumn() ; // gets columns
	ItemType getValue(int row , int col) ; 
	bool Validation( int row , int col ) ; // checks if the row and column is available

 private:
	template <class ItemType>
	struct A  // struct for open and close value
	{
		ItemType open_value ;
		string close_value ; // will be equal to X
		bool closed;
	};
    int rows ;
	int cols ;
	A <ItemType> ** matrix ; // matrix for game


} ;
#include "board.cpp"
#endif

