#include "board.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std ;


template <class ItemType >
Board <ItemType> ::Board ( int row , int col )
{
	rows = row ;
	cols = col  ;
	matrix = new A <ItemType> * [rows] ;
	for ( int i = 0 ; i < rows ; i++)
		matrix[i] = new A<ItemType> [cols] ;
	



}



template <class ItemType>
Board <ItemType >:: ~Board()
{
	for(int i=0; i < rows; i++) {
    delete [] matrix[i];
    }
    delete[] matrix;

	
}



//template <class ItemType >
//void Board <ItemType> ::readBoardFromFile ( ifstream & input )
//{
//	string line ;
//	input.clear() ;
//	input.seekg(0) ;
//	getline ( input , line) ;
//	int row_num = 0 ;
//	int col_num = 0 ;
//	while(getline( input , line))
//	{
//		string word ;
//		istringstream ss(line) ;
//		while( ss >> word)
//		{
//				if( '0' <= word.at(0) && word.at(0) <= '9' ) // if the type is integer
//	            {
//						int new_value = atoi(word) ;
//						matrix[row_num][col_num].open_value = new_value ;
//						matrix[row_num][col_num].close_value = "X" ;
//						matrix[row_num][col_num].closed = true ;
//
//				}
//				else
//				{
//					matrix[row_num][col_num].open_value = word.at(0) ;
//					matrix[row_num][col_num].close_value = "X" ;
//					matrix[row_num][col_num].closed = true ;
//				} 
//
//			col_num += 1 ;
//		}
//		col_num = 0 ;
//		row_num += 1 ;
//	}
//
//}


template <class ItemType >
void Board <ItemType> ::readBoardFromFile ( ifstream & input )
{
	string line ;
	input.clear() ;
	input.seekg(0) ;
	getline ( input , line) ;
	int row_num = 0 ;
	int col_num = 0 ;
	while(getline( input , line))
	{
		ItemType word ;
		istringstream ss(line) ;
		while( ss >> word)
		{
				
					matrix[row_num][col_num].open_value = word ;
					matrix[row_num][col_num].close_value = "X" ;
					matrix[row_num][col_num].closed = true ;
				

			col_num += 1 ;
		}
		col_num = 0 ;
		row_num += 1 ;
	}

}

template <class ItemType >
void Board <ItemType> ::closeCard ( int row , int col )
{
	matrix[row][col].closed = true ;

}



template <class ItemType >
void Board <ItemType> ::CardOpen ( int row , int col )
{
	
	matrix[row][col].closed = false ;

}




template <class ItemType >
void Board<ItemType> ::displayBoard ()
{
	for( int i = 0 ; i < rows ; i ++)
	{
		for( int j = 0 ; j < cols ; j ++)
		{
			if( matrix[i][j].closed == true)
				cout << matrix[i][j].close_value ;
			else
				cout << matrix[i][j].open_value ;
			cout << " " ;
		}

		cout << endl ;
	}
}


template <class ItemType >
ItemType Board<ItemType> ::getValue (int row , int col)
{
	return matrix[row][col].open_value ;
}



template <class ItemType >
int Board <ItemType> ::getRow ()
{
	return rows ;
}

template <class ItemType >
int Board <ItemType>::getColumn ()
{
	return cols ;
}


template <class ItemType>
bool Board<ItemType> :: Validation(int row , int col)
{
	if( (row >= rows) || (col >= cols) || (row < 0) || (col <0) )
		return false ;
	if( matrix[row][col].closed == false )
		return false ;
	return true ;
}

