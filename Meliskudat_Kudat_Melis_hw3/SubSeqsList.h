
#include <iostream>
using namespace std;


struct SubSeqNode
{
int value; 
SubSeqNode * next;
};



struct SubSeqHeadNode
{
int size; // number of elements in the subsequence
SubSeqNode * sHead; // head of the subsequence node list
SubSeqHeadNode * next; // it is connected to the other subseqheadnode

};


class SubSeqsList
{
public:
   SubSeqsList(); 
   void CreateNewSubSeq( int number_to_be_added ) ; // to create subnodes with only 1 size 
   void AppendingSubSeq( int number_to_be_added) ; // to copy the subnodes that are smaller than the number to be added and then to merge them
   void Deletion ( int number) ; // to delete lists that involve the -1 * user_input
   void Sorting() ; // to sort the lists in an order
   void Comparison(int xsize) ; // to make comparison between the lists
   bool ComparisonBetweenSizes( SubSeqHeadNode* temp , SubSeqHeadNode* temp2); // to be called in the "comparison func" and is used to compare lists with the same size
   SubSeqNode* CopyList ( SubSeqHeadNode *head , int number_to_be_added) ; // to copy the list and merge it with the new number
   void ToDisplay ( SubSeqHeadNode* temp) ; // to display the final version and is called in the "comparison func"
   bool IsInList ( int number_to_be_added) ; // to check if the number is already in the list or not
   void DeleteAllList() ; // to delete the list after it is finished
private:
SubSeqHeadNode * hHead; // the head of the list
int tonew ; // to prevent adding the same number
};

