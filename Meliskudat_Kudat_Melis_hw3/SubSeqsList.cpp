#include "SubSeqsList.h" // including the header
#include <iostream>

SubSeqsList ::SubSeqsList()
{
	hHead = NULL ; // making head equal to null
	tonew = 0 ; 
}

void SubSeqsList ::DeleteAllList() // this func is used to delete all nodes at the end of the program
{
	SubSeqHeadNode* ptr = hHead ;
	while( hHead)
	{
		hHead = hHead->next ; 
		delete ptr ;
		ptr = hHead ;
	}
}


bool SubSeqsList :: IsInList( int number_to_be_added)
{
	  
	SubSeqHeadNode* ptr = hHead ;
	while( ptr != NULL)
	{
		if( ptr ->sHead ->value == number_to_be_added) // if already in the list
			return true ;
		ptr = ptr ->next ;
	}
	return false ;


}



void SubSeqsList :: Deletion(int number)
{
	    SubSeqHeadNode* ptr ;
		ptr = hHead ;
		int count = 0 ; // to see if there is a list that is deleted 
		while( ptr!= NULL )
		{
			bool isInTheList = false ;
			SubSeqNode* pint = ptr->sHead ;
			while( pint != NULL)
			{
				if( pint ->value == -1 * number) // if number * -1 exists in the list then it should be deleted
				{
					isInTheList = true ;
					break ;
				}
				pint = pint ->next ;
			}
			if( isInTheList == true) // meaning that we have to make deletion
			{
				if( ptr == hHead) // if the deleted one is the head
				{
					SubSeqHeadNode* tobedeleted = hHead ;
					hHead = hHead  ->next ;
					ptr = ptr ->next ;
					delete tobedeleted ;
					count += 1 ; // since it is deleted the count should be increased
				}
				else  if( ptr != hHead && ptr ->next != NULL) // if the deleted one is not head nor tail but in the middle
				{
					SubSeqHeadNode* forthemiddle = hHead ;
					while( forthemiddle ->next != ptr)
						forthemiddle = forthemiddle ->next ;
					ptr = forthemiddle ;
					SubSeqHeadNode* temp = ptr ->next ;
					ptr->next = temp->next ;
					delete temp;
					ptr = ptr ->next;
					count += 1;
				}
				else if( ptr != hHead && ptr ->next == NULL) // if the deleted one is the tail 
				{
					SubSeqHeadNode* fortheend = hHead ;
					while( fortheend ->next != ptr)
						fortheend = fortheend ->next ;
					ptr = fortheend ;
					fortheend = ptr ->next ;
					delete fortheend ;
					ptr ->next = NULL ;
					count+= 1 ;
				}

			}
			else
			{
				ptr = ptr ->next ;
			}

		}
		if( count == 0) // there is no list that contains -1* number
			cout << "There is no subsequence that contains " << (-1 *number) << " to be deleted" << endl ;
		else
		  cout << "All subsequence(s) containing " << (-1 *number) <<" has/have been deleted" << endl ;

	
}

/* Begin: code taken from copyLinkedList.cpp and edited */
SubSeqNode * SubSeqsList :: CopyList( SubSeqHeadNode * ptr , int number_to_be_added)
{
	 SubSeqNode * pint ;
	 pint = ptr ->sHead;
	 SubSeqNode *fornew = new SubSeqNode; // to make the copy of the first element
	 fornew ->value = pint ->value ;
	 fornew ->next = NULL ;
	 SubSeqNode* tokeeptrack = fornew; // to keep the track
	 while( pint ->next != NULL)
	 {
		 tokeeptrack ->next  = new SubSeqNode ;
		 tokeeptrack ->next->value = pint ->next ->value ;
		 tokeeptrack ->next ->next = NULL ;
		 pint = pint ->next ;
		 tokeeptrack = tokeeptrack ->next ;

	 }
	 SubSeqNode* addtothelast ;
	 addtothelast = new SubSeqNode ;
	 addtothelast ->value = number_to_be_added ;
	 addtothelast ->next = NULL ;
	 tokeeptrack ->next = addtothelast ;
	 return fornew;

}
/* End: code taken from copyLinkedList.cpp and edited */

void SubSeqsList :: CreateNewSubSeq( int number_to_be_added ) // to make lists with size 1
{
	if( IsInList( number_to_be_added) == true) // if the number shouldn't be included again
	{
		tonew += 1; // it is used in the Appending func , telling Appending function that this number already exists in the list so if tonew != 0 do not append
		cout << number_to_be_added << " is already in the list!" << endl ;
	} 
	else
	{
		SubSeqNode * ptr ;
		ptr = new SubSeqNode ;
		ptr ->value = number_to_be_added ;
		ptr -> next = NULL ;
		SubSeqHeadNode * pint ;
		pint = new SubSeqHeadNode ;
		pint ->size = 1 ;
		pint ->next = NULL ;
		pint ->sHead = ptr ;
		if( hHead == NULL )
			hHead = pint ;
		SubSeqHeadNode * pointer_x ;
		pointer_x = hHead ;
		while( pointer_x ->next != NULL )
			pointer_x = pointer_x ->next ; // finding the last pointer
		if( hHead != pint)
			pointer_x ->next = pint ; // adding new list to the end
		cout << "Subsequence(s) containing " << number_to_be_added << " has/have been added" << endl;
	}
}

void SubSeqsList :: AppendingSubSeq( int number_to_be_added)
{
	if( tonew == 0 )
	{
		SubSeqHeadNode * ptr ;
		ptr = hHead ;
		while( ptr ->next != NULL )
		{
			if( ptr -> sHead != NULL)
			{
				bool isOrder = true ; // to check if all the elements of the list is smaller than the value to be added
				SubSeqNode * pint ;
				pint = ptr ->sHead ;
				while( pint != NULL )
				{
					if( pint ->value >= number_to_be_added)
					{
						isOrder = false ; // if false it means that you cannot add the number to the list
					}
					pint = pint ->next ;
				}
				if( isOrder == true) // means that you can add new list
				{
					SubSeqHeadNode * tobeadded ;
					tobeadded = new SubSeqHeadNode ;
					SubSeqNode * pointr ;
					pointr = ptr ->sHead ;
					int count = 1 ;
					while( pointr != NULL)
					{
						count += 1 ;
						pointr = pointr ->next ;
					
					}
					SubSeqNode * listtobeadded = CopyList( ptr, number_to_be_added) ;
					tobeadded ->size = count ;
					tobeadded ->next = NULL ;
					tobeadded ->sHead = listtobeadded ;
				
					SubSeqHeadNode * tofindend = ptr ;
					while( tofindend ->next != NULL)
						tofindend = tofindend ->next ; // finding the last pointer
					tofindend ->next = tobeadded ; // adding the new list to the end
				}

			}
			ptr = ptr ->next ;
		}
	}
	tonew = 0 ; // after appending is finished this should be equalized to 0 for the new numbers that will come
}


void SubSeqsList :: Sorting()
{
	if( hHead == NULL)
	  cout << "List is empty!" << endl ;

	else{
		SubSeqHeadNode* ptr = hHead ;
		SubSeqHeadNode* pint = hHead ;
		SubSeqHeadNode* pinter = hHead ;
	
		int total = 0 ; // to see how many elements exist in the linked list
		while( pint != NULL)
		{
			total += 1 ;
			pint = pint ->next ;
		}
		int xSize = 1 ;
	
		int max_size = 0 ; // max size among the list
		while(ptr != NULL)
		{
			if( ptr ->size > max_size)
				max_size = ptr ->size ;
			ptr = ptr ->next ;
		}

		for( int i = 0 ; i < max_size ; i++)
		{
			Comparison(xSize) ; // to make the order and to display
			xSize += 1 ;
		}
	}

}



void SubSeqsList  :: Comparison(int xsize)
{
	SubSeqHeadNode* ptr = hHead ;
	SubSeqHeadNode* temp = hHead ;
	SubSeqHeadNode* temp2 = hHead ;

	int count = 0;
	while( ptr != NULL)
	{
		if(ptr ->size == xsize)
			count += 1 ;
		ptr = ptr ->next ;
	}


	int x = 0 ; // to be sure that each element with size sizex will be printed
	while( x < count)
	{
		while( temp ->size != xsize && temp!= NULL) // to find the pointer that has the size of xsize
			temp = temp->next ; 
	
		while( temp2 != NULL)
		{
			if( temp2 ->size == xsize && temp2 != temp) 
			{
				if( ComparisonBetweenSizes( temp , temp2) == false) // temp2 is smaller
				{
					temp = temp2 ; // update temp with the smaller value
				}
			}
			temp2 = temp2 ->next ;
		}
		ToDisplay(temp) ; // to display the list
		temp ->size = 0 ;
		x += 1 ;
		temp = hHead;
		temp2 = hHead ;
	}	


	
}


void SubSeqsList :: ToDisplay( SubSeqHeadNode* temp)
{
	cout << temp ->size << "  |  ";
	SubSeqNode* pint = temp ->sHead ;
	int number ;
	while( pint -> next != NULL)
	{
		number = pint ->value ; // printing value
		cout << number << " --> " ; // printing the symbol
		pint = pint ->next ; 
	}
	number = pint ->value ; // printing the next value
	cout << number ;
	cout << endl ;
}



bool SubSeqsList  :: ComparisonBetweenSizes( SubSeqHeadNode* temp , SubSeqHeadNode* temp2)
{
	
	SubSeqNode* tempnode = temp ->sHead ;
	SubSeqNode* temp2node = temp2 ->sHead ;
	if(tempnode ->next == NULL) // if we compare the lists with size 1
	{
		if (temp2node ->value < tempnode ->value) // if temp2 should be printed first
			return false;
		else
			return true ;
	}


	while( tempnode!= NULL && tempnode ->next != NULL)
	{
		
		if( temp2node ->value < tempnode ->value)
			return false ; // temp2 is smaller , thus should be printed first
		tempnode = tempnode->next;
		temp2node = temp2node ->next ;
	}
	return true; // temp is smaller, keep it

		


	


}
