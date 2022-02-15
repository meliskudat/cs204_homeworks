#include "player.h"
#include "board.h"
#include<iostream>
#include<string>

using namespace std;

template <class ItemType >
Player <ItemType> :: Player( Board<ItemType>& myboard) : board(myboard), numberofsuccess(0){}


template <class ItemType >
ItemType Player <ItemType> :: openCard ( int row , int col)
{
	board.CardOpen( row , col ) ;
	return board.getValue(row , col) ;
}

template < class ItemType >
bool Player <ItemType> :: validMove ( int row , int col )
{
		return board.Validation( row , col ) ;
}


template < class ItemType >
void Player <ItemType> :: increaseNumberOfSuccess()
{
	numberofsuccess += 1 ;
}

template < class ItemType >
int Player <ItemType> :: getNumberOfSuccess()
{
	return numberofsuccess ;
}