#include <iostream>
#include <string>
#include <sstream> // used for istringstream
#include "strutils.h" // it is used for itoa

// Melis KUDAT's Program

using namespace std;

struct node
{
	int value ;
	node* next ;
};



void DeleteAllList(node* &head) // this func is used to delete all nodes at the end of the program
{
	node* ptr = head ;
	while( head)
	{
		head = head->next ;
		delete ptr ;
		ptr = head ;
	}
}



bool IfAlreadyExists ( node* head , int number ) // this func is used to check whether the number is already existing in the list or not
{
	node * ptr = head ;
	while( ptr != NULL )
	{
		if ( ptr-> value == number) // if exists
			return true ;
		ptr = ptr -> next ;
	}
	return false ;
}
/* Begin: code taken from ptrfunc.cpp and updated*/
void DisplayList (node * head) // this func is used to display the list after deletion and insertion is finished for each number
{
	cout << "List content: ";
	node * ptr = head;
    while (ptr != NULL) // until the end of the list
	{
		cout << ptr ->value << " "; 
		ptr = ptr->next; // move to the next 
	}
	cout << endl<<endl;
}
/* End: code taken from ptrfunc.cpp and updated */


void DisplayTheLastList (node * head) // after all the displays this function displays the last version of the list
{
	node * ptr = head;
    while (ptr != NULL) 
	{
		cout << ptr ->value << " "; // the value that ptr points to
		ptr = ptr->next;
	}
	cout << endl<<endl;
}


void DeletionForAscending ( node* &head , int number ) // this func is to delete numbers that exist in the list but bigger than the number
{
	node* ptr = head ; 
	int count = 0 ; // if nothing is deleted this will count
	string s = "Deleted Nodes:" ;  // to print the deleted notes a string variable is made and will be updated in the func
	string x = "" ;
	while( ptr != NULL)
	{
			if( head == ptr && head ->value > number && ptr -> next == NULL ) // if the list has only "head" and no other while also head being bigger than the number
			{
				int n = head->value;
				delete head; 
				head = NULL; // since our head will be change in the insertion func we cleared head
				ptr = NULL;
				int a = n ;
				string b = itoa(a) ;
				s += ' ' + b ; // adding the deleted node to s
				count += 1 ; // increasing count so that we can understand at least one node is deleted			
	        }
			
		     else if( ptr != NULL && ptr -> next != NULL && ptr -> next -> value >  number) // if ptr doesn't point the last element and ptr's next's value is bigger than the number
			{
				 node* temp = ptr -> next ;
				 ptr -> next = temp -> next ; 
				
				  int x = temp ->value ; // this is the value to be added to deleted nodes string
				  string y = itoa(x) ; // converting temp -> value to string to add this to s 
				  s += ' ' + y ;
				  delete temp ;
				  count += 1 ;
				 
			}
			else if( ptr ->next == NULL && ptr ->value > number) //  if ptr points the last element and it is bigger than the number
			{
				int x = ptr ->value ;
		        string y = itoa(x) ; // converting temp -> value to string to add this to s 
		    	s += ' ' + y ;
				ptr = head ;
				ptr ->next = NULL ;
				count += 1 ;
			}
			if ( ptr!= NULL && ptr ->next != NULL && ptr ->next ->value > number) 
			 ptr = ptr;
			else if( ptr == NULL && head == NULL ) // if head was deleted and then was equalized to NULL in the previous lines we shouldn't go to the ptr -> next since it is not correct 
				ptr = ptr ;
			else
				ptr = ptr -> next ; // go to the next ptr
	}
	
	if( head != NULL && head -> value > number ) // if we change the head
	{
		int value = head -> value ;
		string valuestr = itoa(value) ;
		s = s.substr(0,15) + ' ' + valuestr + ' ' + s.substr(15,s.length()) ; // adding the deleted head value to the beginning of the deleted ones
		delete head ;
		head = NULL ;
		
	}

	if( count == 0 ) // if nothing is deleted
	{
		s+= " None" ;
	}
	 cout << s << endl ; // cout the deleted ones
}


void InsertionForAscending( node* &head , int number)
{ 
	if( IfAlreadyExists( head, number) == false)
		DeletionForAscending(head , number ) ;
	if( head == NULL ) // if head doesn't have a value we have to update it with the number
	{
		    
		    head = new node ;				
			head->value = number ;
			head->next = NULL ;
			cout << "Appended: " << number << endl;		
	}

	else if( head != NULL && IfAlreadyExists(head, number) == false) // if we are adding to a list that has head
	{
		
		node* ptr ;
		ptr = head ;
		if( head == NULL)
		{
			head = new node ;				
			head->value = number ;
			head->next = NULL ;
			cout << "Appended: " << number << endl;

		}
		else
		{
			while ( ptr -> next != NULL) // to reach the last one
			{
				ptr = ptr -> next ;
			}
			node* pint = new node ; // to insert new node to the end of the list
			pint -> value = number ;
			pint -> next = NULL ;
			ptr -> next = pint ;
			cout << "Appended: " << number << endl;	
		}
	}
	else if( IfAlreadyExists( head, number) == true) // if number is already in the list
	{
		cout << number << " is already in the list! " << endl ;
	}	
}

void DeletionForDescending ( node* &head , int number )
{
	node* ptr = head ; // to be sure that we don't change the head
	int count = 0 ; // if nothing is deleted this will count
	string s = "Deleted Nodes:" ; 
	string x = "" ;
	while( ptr != NULL)
	{
			if( head == ptr && head ->value < number && ptr -> next == NULL ) {
				int n = head->value;
				delete head; 
				head = NULL; 
				ptr = NULL;
				int a = n ;
				string b = itoa(a) ; // converting temp -> value to string to add this to s 
				s += ' ' + b ;
				count += 1 ;			
	        }
			
		     else if( ptr != NULL && ptr -> next != NULL && ptr -> next -> value <  number)
			{
				 node* temp = ptr -> next ;
				 ptr -> next = temp -> next ;
				
				  int x = temp ->value ;
				  string y = itoa(x) ; // converting temp -> value to string to add this to s 
				  s += ' ' + y ;
				  delete temp ;
				  count += 1 ;
				 
			}
			else if( ptr ->next == NULL && ptr ->value < number)
			{
				int x = ptr ->value ;
		        string y = itoa(x) ; // converting temp -> value to string to add this to s 
		    	s += ' ' + y ;
				ptr = head ;
				ptr ->next = NULL ;
				count += 1 ;
			}
			if ( ptr!= NULL && ptr ->next != NULL && ptr ->next ->value < number)
			 ptr = ptr;
			else if( ptr == NULL && head == NULL )
				ptr = ptr ;
			else
				ptr = ptr -> next ;
	}
	
	if( head != NULL && head -> value < number )
	{
		int value = head -> value ;
		string valuestr = itoa(value) ;
		s = s.substr(0,15) + ' ' + valuestr + ' ' + s.substr(15,s.length()) ;
		delete head ;
		head = NULL ;
		
	}

	if( count == 0 ){
		s+= " None" ;
	}
	 cout << s << endl ;
}


void InsertionForDescending( node* &head , int number)
{ 
	if( IfAlreadyExists( head, number) == false)
		DeletionForDescending(head , number ) ;
	if( head == NULL )
	{
		    head = new node ;				
			head->value = number ;
			head->next = NULL ;
			//cout << "Deleted nodes: None" << endl ;
			cout << "Appended: " << number << endl;		
	}

	else if( head != NULL && IfAlreadyExists(head, number) == false)
	{
		
		node* ptr ;
		ptr = head ;
		if( head == NULL)
		{
			
			head = new node ;				
			head->value = number ;
			head->next = NULL ;
			cout << "Appended: " << number << endl;

		}
		else
		{
		
			while ( ptr -> next != NULL)
			{
				ptr = ptr -> next ;
			}
			node* pint = new node ;
			pint -> value = number ;
			pint -> next = NULL ;
			ptr -> next = pint ;
			cout << "Appended: " << number << endl;	
		}
	}
	else if( IfAlreadyExists( head, number) == true)
	{
		cout << number << " is already in the list! " << endl ;
	}	
}

int main()
{
	bool OrderCheck = true ;
	string mode ,movement , numbers ;
	cout << "Please enter the order mode (A/D): " ;
	
	while(getline(cin,mode)) 
	{
		
		istringstream input(mode) ;
		input >> movement  ;
		if( movement == "A" )
		{
			OrderCheck = true ; // if true it means "ascending"
			break ;
		}
		else if(movement == "D") 
		{
			OrderCheck = false ; // if false it means "descending"
			break ;
		}
		else
		{
			cout << "Please enter the order mode again (A/D): " ;
		}
	
	}
	cout << "Please enter the numbers in a line: " ;
	getline( cin , numbers) ;
	if( numbers.empty()) // if nothing is deleted as input for the numbers
	{
		cout << endl ;
		cout << "The list is empty at the end of the program and nothing is deleted" << endl ;
	}
	else{
		cout << endl ;
		cout << endl ;
		string number ;
		int int_number ;
		istringstream input(numbers) ;
		node* head ; // making a pointer that points to head
		head = NULL ;
		while( input >> number) // for each number
		{
			int_number = stoi(number)  ;
			if( OrderCheck == true) // mode is "A" ;
			{
				 cout << "Next Number: " << int_number << endl ; 
				 InsertionForAscending ( head , int_number) ; // to delete and insert
				 DisplayList ( head) ; // to print the list
				 cout << endl ;
			 
			
			}
			else if( OrderCheck == false) // mode is "B"
			{
				cout << "Next Number: " << int_number << endl ; 
				InsertionForDescending( head, int_number) ;
				DisplayList( head) ;
				cout << endl ;
			}


		}
		cout << "All the nodes are deleted at the end of the program: " ;
		DisplayTheLastList(head) ; // last version of the list
		DeleteAllList(head) ; 
	}
	return 0;
}