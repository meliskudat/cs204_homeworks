#ifndef PLAYER_H
#define PLAYER_H
#include "board.h"
#include<string>
#include<iostream>
using namespace std;


template < class ItemType >
class Player 
{

  public :
	  Player() ; // constructor
	 Player( Board<ItemType> & myboard ) ; // constructor that initializes board
	  ItemType openCard ( int row , int col ) ;  // calls board class
	  bool validMove ( int row , int col ) ; // checks if the row and column is available
	  void increaseNumberOfSuccess() ; // increases number of success
	  int getNumberOfSuccess() ; // returns number of succeses

  private: 
	  Board <ItemType>& board ; // shares board
	  int numberofsuccess ; 

};
#include "player.cpp"
#endif
