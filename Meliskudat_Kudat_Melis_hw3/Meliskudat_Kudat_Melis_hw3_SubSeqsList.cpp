#include <iostream>
#include <string>
#include <sstream> // to use istringstream
#include "SubSeqsList.h" // to use the SubSeqLists class and the structs

// Melis KUDAT's program


using namespace std ;

int main()
{
	string line , number ;
	int numint ;
 	cout << "Please enter the numbers in a line: " ;
	getline( cin , line) ;
	cout << endl ;
	if( line.empty()) // if nothing is deleted as input for the numbers
	{
		cout << endl ;
		cout << "FINAL CONTENT" << endl ;
		cout << "List is empty!" << endl ;
	}
	else
	{
		istringstream  input (line) ; // to analyze numbers one by one
		SubSeqsList Structure ;
		while( input >> number)
		{
			numint = stoi( number) ;
			if(numint >= 0 )
			{
				Structure.CreateNewSubSeq(numint) ; // first lists with one size should be created
				Structure.AppendingSubSeq(numint) ; // after lists should be appended by rules
			}
			else if(numint < 0 ) // if <0 then deleting func should be called
			{
				Structure.Deletion(numint) ;
			}

		}
		cout << endl ;
		cout << "FINAL CONTENT " << endl ;
		Structure.Sorting() ;
		Structure.DeleteAllList() ; // after it is finished the list should be deleted
	}
	return 0 ;
	

}
