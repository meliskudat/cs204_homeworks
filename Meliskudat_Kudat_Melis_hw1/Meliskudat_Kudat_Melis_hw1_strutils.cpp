#include <iostream>
#include <vector> // to create matrix
#include <string> 
#include <fstream> // to read files
#include <sstream> // to use istringstream to take variables in a line one by one
#include "strutils.h"  // to use atoi which converts from string to integer

// Melis KUDAT's program
using namespace std ;

bool RowColCheck ( ifstream & file) // func to see if the row and column numbers of matrix are positive or not
{
	string line ;
	string number ;
	file.clear() ; 
	file.seekg(0) ; // with that we will be sure that we are starting to search from the first line
	getline(file, line) ; // with that "line" will be equal to the first line
	istringstream input(line) ; 
	while ( input >> number) // this will take words until all words are taken in the line
	{
		if(number <= "0" ) // since the row and the column number cannot be < 0 
			return false ;
	}
	return true ;
}

bool CheckCorrectness ( string line) // func to check if the line has 5 qualities ( word, row, column, direction and orientation)
{
	string letter ;
	istringstream input(line) ;
	int count = 0 ; // to count if a line has 5 qualities
	while( input >> letter) // this loop is to take words until all words are taken in the line
	{
		count += 1 ;
	}
	if(count == 5 )
		return true ;
	return false ;

}



void CleanedMatrix ( vector<vector<char>> & matrix) 
	// in the WordinMatrix function we continued to fill the matrix with the spesific word until one of the letters was failed to be put in the matrix
	// but even if there was a word that failed for example in the 3rd letter yet we already put the first two letters into the matrix
	// in the WordinMatrix function we put those letters as '+'
	// now since the word failed we have to change the letters we already put to the matrix into to their previous version which was '-' 
{
	for(int i = 0 ; i < matrix.size() ; i++)
	{
		for(int j = 0 ; j < matrix[0].size() ; j++)
		{
			if( matrix[i][j] == '+')
			{
				matrix[i][j] = '-' ;
			}

		}
	}
}


bool WordinMatrix( string word, int wordrow, int wordcol, string direction , string orientation , int rows , int columns , vector<vector<char>> & matrix) 
	// this func will check the next movement if possible ( such as to up, down )and if not return false , but if possible it will change the matrix[x][y] from "-" to "+" that provides the possible movement
	// if all the letters of the word were put successfully then it will change them from "+" to the original letter
{
	

	if( matrix[wordrow][wordcol] != '-' )
	{
		return false ;
	}
	else if( matrix[wordrow][wordcol] == '-')
	{
			if( direction == "r" && orientation == "CW")
			{
				matrix[wordrow][wordcol] = '+' ;
				int currentrow = wordrow ;
				int currentcolumn = wordcol ;
				int length = word.length() ;
				int count = 1 ; // since we put the first letter to the matrix we already have one letter in the matrix , so count = 1
				for(int i = 1 ; i < length ; i++)
				{
						if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '-') // to check if right is possible
						{
								matrix[currentrow][currentcolumn+1] = '+' ; // changing it to '+' , in the following part we will change it to the original letter
								count += 1 ; // increasing count to compare with the word length at the end of the loop
								currentcolumn += 1 ; // updating the column according to the movement
						}
						else if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '-') // if right is not possible to check if down is possible
						{
								matrix[currentrow+1][currentcolumn] = '+' ;
								count += 1;
								currentrow += 1 ;
						}
						else if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '-' ) // if down is not possible to check left
						{
							    matrix[currentrow][currentcolumn-1] = '+' ;
								count +=1  ;
								currentcolumn -= 1 ;
							
						}
						else if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '-') // if down is not possible to check if up is possible
						{
								matrix[currentrow-1][currentcolumn] = '+' ;
								count += 1;
								currentrow -= 1 ;							
						}
						else
						{
							return false ;
						}
			        
				}
				if(count == length){ // if count = length , then it means all of the letters of the word can successfully be put into the matrix
					matrix[wordrow][wordcol] = word.at(0) ;
					currentrow = wordrow ;
					currentcolumn = wordcol ;
					for(int i = 1 ; i < length ; i++)
					{
							if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '+') // to check if right is possible
							{
									matrix[currentrow][currentcolumn+1] = word[i] ; // to change '+' to the original letter
									currentcolumn += 1 ;
							}
							else if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '+') // if right is not possible to check if down is possible
							{

									matrix[currentrow+1][currentcolumn] = word[i] ;
									currentrow += 1 ;
							}
							else if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '+' ) // if down is not possible to check left
							{
									matrix[currentrow][currentcolumn-1] = word[i] ;
									currentcolumn -= 1 ;
							
							}
							else if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '+') // if down is not possible to check if up is possible
							{
		
									matrix[currentrow-1][currentcolumn] = word[i] ;
									currentrow -= 1 ;							
							}
							else
							{
								return false ;
							}
			        
					}
				}
				
			}
			else if(direction == "r" && orientation == "CCW")
			{
				matrix[wordrow][wordcol] = '+' ;
				int currentrow = wordrow ;
				int currentcolumn = wordcol ;
				int length = word.length() ;
				int count = 1 ;
				for(int i = 1 ; i < length ; i++)
				{
						if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '-' ) // to check if right is possible
						{		
								matrix[currentrow][currentcolumn+1] = '+' ;
								count += 1 ;
								currentcolumn += 1 ;							
						}
						else if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '-') // if right is not possible to check if up is possible
						{		
							    matrix[currentrow-1][currentcolumn] = '+' ;
								count += 1;
								currentrow -= 1 ;
						
						}
						else if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '-' ) // if up is not possible to check left
						{
								matrix[currentrow][currentcolumn-1] = '+' ;
								count += 1 ;
								currentcolumn -= 1 ;							
						}
						else if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '-' ) // if left is not possible to check if down is possible
						{
								matrix[currentrow+1][currentcolumn] = '+' ;
								count +=1 ;
								currentrow += 1 ;						
						}
						else
						{
							return false ;
						}
				}
				if(count == length)
				{
					matrix[wordrow][wordcol] = word.at(0) ;
					currentrow = wordrow ;
					currentcolumn = wordcol ;
					for(int i = 1 ; i < length ; i++)
					{
							if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '+' ) // to check if right is possible
							{					
									matrix[currentrow][currentcolumn+1] = word[i] ;
									currentcolumn += 1 ;							
							}
							else if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '+') // if right is not possible to check if up is possible
							{							
									matrix[currentrow-1][currentcolumn] = word[i] ;
									currentrow -= 1 ;
						
							}
							else if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '+' ) // if up is not possible to check left
							{

									matrix[currentrow][currentcolumn-1] = word[i] ;
									currentcolumn -= 1 ;							
							}
							else if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '+' ) // if left is not possible to check if down is possible
							{
							
									matrix[currentrow+1][currentcolumn] = word[i] ;
									currentrow += 1 ;						
							}
							else
							{
								return false ;
							}
						}
				}
				
			}
			else if( direction == "l" && orientation == "CW")
			{
				matrix[wordrow][wordcol] = '+' ;
				int currentrow = wordrow ;
				int currentcolumn = wordcol ;
				int length = word.length() ;
				int count = 1 ;
				for(int i = 1 ; i < length; i++)
				{
					if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '-' ) // to check if left is possible
					{
								count += 1 ;
								matrix[currentrow][currentcolumn-1] = '+' ;
								currentcolumn -= 1 ;
							
					}
					else if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '-') // if left is not possible to check if up is possible
					{
							
								count += 1 ;
								matrix[currentrow-1][currentcolumn] = '+' ;
								currentrow -= 1 ;
					
					}
					else if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '-' ) // if left is not possible to check if right is possible
					{
							    count += 1 ;
								matrix[currentrow][currentcolumn+1] = '+' ;
								currentcolumn += 1 ;
							
					}
					else if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '-') // if right is not possible to check if down is possible
					{
								count += 1 ;						
								matrix[currentrow+1][currentcolumn] = '+' ;
								currentrow += 1 ;
							
					}
					else
					{
						return false ;					
					}
				}
				if( count == length) {
					matrix[wordrow][wordcol] = word.at(0) ;
					currentrow = wordrow ;
					currentcolumn = wordcol ;
					for(int i = 1 ; i < length; i++)
					{
						if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '+' ) // to check if left is possible
						{
									matrix[currentrow][currentcolumn-1] = word[i] ;
									currentcolumn -= 1 ;
							
						}
						else if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '+') // if left is not possible to check if up is possible
						{
							
						
									matrix[currentrow-1][currentcolumn] = word[i] ;
									currentrow -= 1 ;
					
						}
						else if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '+' ) // if left is not possible to check if right is possible
						{
							
									matrix[currentrow][currentcolumn+1] = word[i] ;
									currentcolumn += 1 ;
							
						}
						else if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '+') // if right is not possible to check if down is possible
						{
														
									matrix[currentrow+1][currentcolumn] = word[i] ;
									currentrow += 1 ;
							
						}
						else
						{
							return false ;					
						}
				  }
			   }
			}
			else if( direction == "l" && orientation == "CCW")
			{
				matrix[wordrow][wordcol] = '+' ;
				int currentrow = wordrow ;
				int currentcolumn = wordcol ;
				int length = word.length() ;
				int count = 1 ;
				for(int i = 1 ; i < length ; i++)
				{
					if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '-') // to check if left is possible
					{			
								count += 1 ;
								matrix[currentrow][currentcolumn-1] = '+';
								currentcolumn -= 1 ;
							
					}
					else if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '-' ) // if left is not possible to check if down is possible
					{
								count += 1 ;					
								matrix[currentrow+1][currentcolumn] = '+' ;
								currentrow += 1 ;							
					}	
		    		else if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '-') // if down is not possible to check if right is possible
					{
								count += 1 ;
								matrix[currentrow][currentcolumn+1] = '+' ;
								currentcolumn += 1 ;							
					}
					else if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '-' ) // if right is not possible to check if up is possible
					{							
								count += 1 ;
								matrix[currentrow-1][currentcolumn] = '+' ;
								currentrow -= 1 ;		
					}
				
					else
					{
						return false ;					
					}

				}
				if( count == length)
				{
					matrix[wordrow][wordcol] = word.at(0) ;
					currentrow = wordrow ;
					currentcolumn = wordcol ;
					for(int i = 1 ; i < length ; i++)
				    {
						if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '+') // to check if left is possible
						{							
									matrix[currentrow][currentcolumn-1] = word[i] ;
									currentcolumn -= 1 ;
							
						}
						else if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '+' ) // if left is not possible to check if down is possible
						{
													
									matrix[currentrow+1][currentcolumn] = word[i] ;
									currentrow += 1 ;							
						}	
		    			else if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '+') // if down is not possible to check if right is possible
						{
							
									matrix[currentrow][currentcolumn+1] = word[i] ;
									currentcolumn += 1 ;							
						}
						else if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '+' ) // if right is not possible to check if up is possible
						{							
							
									matrix[currentrow-1][currentcolumn] = word[i] ;
									currentrow -= 1 ;		
						}
				
						else
						{
							return false ;					
						}

				     }
				}
			}
			else if( direction == "d" && orientation == "CW")
			{
				matrix[wordrow][wordcol] = '+' ;
				int currentrow = wordrow ;
				int currentcolumn = wordcol ;
				int length = word.length() ;
				int count = 1 ;
				for(int i = 1 ; i < length ; i++)
				{
					if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '-' ) // to check if down is possible
					{				
								count += 1 ;
								matrix[currentrow+1][currentcolumn] = '+' ;
								currentrow += 1 ;		
					}
					else if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '-') // if down is not possible to check if left is possible
					{
							
								count += 1 ;
								matrix[currentrow][currentcolumn-1] = '+' ;
								currentcolumn -= 1 ;
							
					}
					else if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '-') // if left is not possible to check if up is possible
					{
								count += 1 ;						
								matrix[currentrow-1][currentcolumn] = '+' ;
								currentrow -= 1 ;							
					}
					else if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '-') // if up is not possible to check if right is possible
					{
								count += 1 ;			
								matrix[currentrow][currentcolumn+1] = '+' ;
								currentcolumn += 1 ;							
					}
					else
					{
						return false ;					
					}
				}
				if( count == length){
					matrix[wordrow][wordcol] = word.at(0) ;
					currentrow = wordrow ;
					currentcolumn = wordcol ;
					for(int i = 1 ; i < length ; i++)
					{
						if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '+' ) // to check if down is possible
						{							
									matrix[currentrow+1][currentcolumn] = word[i] ;
									currentrow += 1 ;		
						}
						else if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '+') // if down is not possible to check if left is possible
						{
							
						
									matrix[currentrow][currentcolumn-1] = word[i] ;
									currentcolumn -= 1 ;
							
						}
						else if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '+') // if left is not possible to check if up is possible
						{
														
									matrix[currentrow-1][currentcolumn] = word[i] ;
									currentrow -= 1 ;							
						}
						else if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '+') // if up is not possible to check if right is possible
						{
											
									matrix[currentrow][currentcolumn+1] = word[i] ;
									currentcolumn += 1 ;							
						}
						else
						{
							return false ;					
						}
				    }
				}		
			}
			else if( direction == "d" && orientation == "CCW")
			{
				matrix[wordrow][wordcol] = '+' ;
				int currentrow = wordrow ;
				int currentcolumn = wordcol ;
				int length = word.length() ;
				int count = 1 ;
				for(int i = 1 ; i < length ; i++)
				{
					if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '-') // to check if down is possible
					{
								count += 1 ;
								matrix[currentrow+1][currentcolumn] = '+' ;
								currentrow += 1 ;
							
					}
					else if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '-') // if down is not possible to check if right is possible
					{
							
								count += 1 ;
								matrix[currentrow][currentcolumn+1] = '+' ;
								currentcolumn += 1 ;
							
					}
					else if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '-') // if right is not possible to check if up is possible
					{
							
								count += 1 ;
								matrix[currentrow-1][currentcolumn] = '+' ;
								currentrow -= 1 ;
							
					}
					else if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '-' ) // if up is not possible to check if left is possible
					{
							
								count += 1 ;
								matrix[currentrow][currentcolumn-1] = '+' ;
								currentcolumn -= 1 ;
							
					}
					else
					{
						return false ;					
					}
				}
				if( count == length){
					matrix[wordrow][wordcol] = word.at(0) ;
					currentrow = wordrow ;
					currentcolumn = wordcol ;
					for(int i = 1 ; i < length ; i++)
					{
						if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '+') // to check if down is possible
						{
									matrix[currentrow+1][currentcolumn] = word[i] ;
									currentrow += 1 ;
						}
						else if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '+') // if down is not possible to check if right is possible
						{
									matrix[currentrow][currentcolumn+1] = word[i] ;
									currentcolumn += 1 ;
						}
						else if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '+') // if right is not possible to check if up is possible
						{
									matrix[currentrow-1][currentcolumn] = word[i] ;
									currentrow -= 1 ;			
						}
						else if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '+' ) // if up is not possible to check if left is possible
						{
									matrix[currentrow][currentcolumn-1] = word[i] ;
									currentcolumn -= 1 ;		
						}
						else
						{
							return false ;					
						}
				    }
				}
			}
			else if( direction == "u" && orientation == "CW")
			{
				matrix[wordrow][wordcol] = '+' ;
				int currentrow = wordrow ;
				int currentcolumn = wordcol ;
				int length = word.length() ;
				int count = 1 ;
				for(int i = 1 ; i < length ; i++)
				{
					if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '-') // to check if up is possible
					{	
								count += 1 ;
								matrix[currentrow-1][currentcolumn] = '+' ;
								currentrow -= 1 ;		
					}
					else if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '-') // if up is not possible to check if right is possible
					{
								count += 1 ;
								matrix[currentrow][currentcolumn+1] = '+' ;
								currentcolumn += 1 ;		
					}
					else if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '-') // if right is not possible to check if down is possible
					{
								count += 1 ;
								matrix[currentrow+1][currentcolumn] = '+' ;
								currentrow += 1 ;		
					}
					else if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '-') // if down is not possible to check if left is possible
					{	
								count += 1 ;
								matrix[currentrow][currentcolumn-1] = '+' ;
								currentcolumn -= 1 ;	
					}
					else
					{
						return false ;					
					}
				}
				if( count == length){

					matrix[wordrow][wordcol] = word.at(0) ;
					int currentrow = wordrow ;
					int currentcolumn = wordcol ;
					for(int i = 1 ; i < length ; i++)
					{
						if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '+') // to check if up is possible
						{	
									matrix[currentrow-1][currentcolumn] = word[i] ;
									currentrow -= 1 ;	
						}
						else if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '+') // if up is not possible to check if right is possible
						{
									matrix[currentrow][currentcolumn+1] = word[i] ;
									currentcolumn += 1 ;
						}
						else if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '+') // if right is not possible to check if down is possible
						{
									matrix[currentrow+1][currentcolumn] = word[i] ;
									currentrow += 1 ;
						}
						else if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '+') // if down is not possible to check if left is possible
						{
									matrix[currentrow][currentcolumn-1] = word[i] ;
									currentcolumn -= 1 ;
						}
						else
						{
							return false ;					
						}
				    }
				}
			}
			else if( direction == "u" && orientation == "CCW")
			{
				matrix[wordrow][wordcol] = '+' ;
				int currentrow = wordrow ; 
				int currentcolumn = wordcol ;
				int length = word.length() ;
				int count = 1 ;
				for(int i = 1 ; i < length ; i++)
				{
					if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '-') // to check if up is possible
					{
							
								count += 1 ; // increasing count to compare with the word length at the end of the loop
								matrix[currentrow-1][currentcolumn] = '+' ;
								currentrow -= 1 ; // updating the row accordingly due to the movement of up
							
					}
					else if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '-') // if up is not possible to check if left is possible
					{
							
								count += 1 ;
								matrix[currentrow][currentcolumn-1] = '+' ;
								currentcolumn -= 1 ;
							
					}
					else if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '-') // if left is not possible to check if down is possible
					{
							
								count += 1 ;
								matrix[currentrow+1][currentcolumn] = '+' ;
								currentrow += 1 ;
							
					}
					else if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '-') // if down is not possible to check if right is possible
					{
							
								count += 1 ;
								matrix[currentrow][currentcolumn+1] = '+' ;
								currentcolumn += 1 ;
							
					}
					else
					{
						return false ;					
					}
				}
				if( count == length){
					matrix[wordrow][wordcol] = word.at(0) ;
					currentrow = wordrow ;
					currentcolumn = wordcol ;
					for(int i = 1 ; i < length ; i++)
				    {
						if( currentrow-1 != -1 && matrix[currentrow-1][currentcolumn] == '+') // to check if up is possible
						{
							
							
									matrix[currentrow-1][currentcolumn] = word[i] ;
									currentrow -= 1 ;
							
						}
						else if( currentcolumn-1 != -1 && matrix[currentrow][currentcolumn-1] == '+') // if up is not possible to check if left is possible
						{
							
							
									matrix[currentrow][currentcolumn-1] = word[i] ;
									currentcolumn -= 1 ;
							
						}
						else if( currentrow+1 < rows && matrix[currentrow+1][currentcolumn] == '+') // if left is not possible to check if down is possible
						{
							
							
									matrix[currentrow+1][currentcolumn] = word[i] ;
									currentrow += 1 ;
							
						}
						else if( currentcolumn+1 < columns && matrix[currentrow][currentcolumn+1] == '+') // if down is not possible to check if right is possible
						{
							
							
									matrix[currentrow][currentcolumn+1] = word[i] ;
									currentcolumn += 1 ;
							
						}
						else
						{
							return false ;					
						}
				   }
				}
			}
	}
	return true ;
}





void PrintMatrix( vector<vector<char>> & matrix) // func to print each row and column of the matrix
{
	for(int i = 0 ; i < matrix.size() ; i++)
	{
		for(int j = 0 ; j < matrix[0].size() ; j++)
		{
			cout << matrix[i][j] << "     " ;
		}
		cout << endl ;
	}

}

int main()
{
	int wordrow , wordcol ;
	string word , wordRow , wordColumn , orientation , direction ; // variables that include the name , row number , column number, orientation such as CW and direction such as u
	string filename , letter ;
	string row, column ;
	cout << "Please enter the name of the file: " ;
	cin >> filename ; // getting the filename to be opened from the user
	ifstream file ;
	file.open(filename.c_str()) ; // trying to open the file
	while( file.fail() ) // getting into this loop means file couldn't be opened and with that loop take filename again until it can be opened
	{
		cout << "File name is incorrect, please enter again: " ;
		cin >> filename ;
		file.open(filename.c_str()) ;

	}
	if( RowColCheck( file) == false) // checking if given matrix columns and rows are positive integers
	{
		cout << "Invalid number for row and/or column!" << endl ;
	}
	
	else
	{
		
		file.clear() ;
		file.seekg(0) ;
		string lineRowCol ;
		getline( file, lineRowCol) ;
		istringstream input(lineRowCol) ;
		input >> row ; // taking the row of the matrix
		input >> column ; // taking the column of the matrix
		int rows = atoi(row) ;
		int columns = atoi(column) ;
		vector< vector <char>> matrix(rows , vector <char> (columns , '-')) ; // making a matrix that is composed of "-" for each column and row
	
		while( getline( file, lineRowCol)) // examining line by line 
		{
				istringstream getin(lineRowCol) ;
				getin >> word ; // word to be put in the matrix
				getin >> wordRow ; // starting row of the word
				getin >> wordColumn ; // starting column of the word
				getin >> direction ; // direction ( l , d , u, r) 
				getin >> orientation ; // orientation ( CCW , CW)
				wordrow = atoi(wordRow) ; // to translate string into int
				wordcol = atoi(wordColumn) ; // to translate string into int

				if( wordrow >= rows || wordcol >= columns || wordrow < 0 || wordcol < 0 ) // checking whether the starting column and row of the word are in range or not
				{
					cout << "Starting point is out of range! Point: " << wordrow << "," << wordcol << endl ; 
				}
				else if( (direction != "d") && (direction != "u") && (direction != "l") && (direction != "r") ) // checking whether the direction given is correct or not
				{
					cout << "Invalid input for direction! Direction: " << direction << endl ;
				}
				else if( CheckCorrectness(lineRowCol) == false) // checking if the line has 5 qualities by the function
				{
					cout << "Invalid line! Number of values is different than 5." << endl ;
				}
				else if( orientation != "CCW" && orientation != "CW") // checking whether the orientation given is correct or not
				{
					cout << "Invalid input for orientation! Orientation: " << orientation << endl ;
				}
				else // if there is no problem
				{
				
						if( WordinMatrix( word, wordrow, wordcol , direction , orientation ,rows , columns , matrix) == true)
						{
							cout << '"' << word << '"' << " was put into the matrix with given starting point:  " << wordrow << "," << wordcol << "  direction: " << direction << "  orientation: " << orientation << endl ;

							PrintMatrix(matrix) ; // to print the updated version of matrix
							cout << endl ;
						}
						else // if word was not put successfully
						{
							CleanedMatrix( matrix) ;
							cout << '"' << word <<'"' << " could not be put into the matrix with given starting point:  " << wordrow << "," << wordcol << "  direction: " << direction << "  orientation: " << orientation << endl ;
							PrintMatrix(matrix) ;
							cout << endl ;
						} 
				}
			}
   }
   return 0 ;
}






		
	

