/*list.cpp*/

//
// Originally written by: Prof. Hummel, U. of I. Chicago, Spring 2021
// Author: Sydney Wells, UIC, Spring 2021
// 
// Implements a one-way linked-list with optimized insertion at
// head and tail of list. The nodes contain 2 data values, a string
// and an integer.
//

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

#include "list.h"

using namespace std;



//
// private member functions:
//

//
// inits this list then makes deep copy of other
//
// Time complexity: O(N)
//
void List::initAndDeepCopy(const List& other)
{
   //
   // TODO: init this list, then make copy of other
   //
    
   // initiallizing other 
   this->Head = nullptr;
   this->Count = 0;
   this->Tail = nullptr;
    
    //need the node to start copying
    Node* cur = other.Head;
    
    while (cur != nullptr) {
        
        //use push_back to copy into the list like in proj 5
        this->push_back(cur->Data.Value1, cur->Data.Value2);
        //move to next node
        cur = cur ->Next; 
    }
   
}


// 
// free the nodes in the list and resets to empty
//
// Time complexity: O(N)
//
void List::freeAndReset()
{
   //
   // TODO: free this list, then reset to empty
   //
   Node* cur = this->Head;
    // traversing and deleting
    while (cur != nullptr) {
        
        Node* temp = cur;
        cur = cur->Next;
        delete temp;
    }

   // setting the list to empty
   this->Head = nullptr;
   this->Count = 0;
   this->Tail = nullptr;
}



//
// public member functions:
//

//
// default constructor
//
// Initializes the list to empty.
// 
// Time complexity: O(1)
//
List::List()
{
   this->Head = nullptr;
   this->Tail = nullptr;
   this->Count = 0;
}

//
// copy constructor
//
// Makes a deep copy of the other list into this list.
// 
// Time complexity: O(N)
//
List::List(const List& other)
{
   this->initAndDeepCopy(other);
}

//
// destructor
//
// Frees all memory related to this list, and then resets to empty.
// 
// Time complexity: O(N)
//
List::~List()
{
   this->freeAndReset();
}

//
// assignment operator (e.g. L2 = L;)
//
// Makes a deep copy of the other list into this list; since this
// list already exists, the existing elements of this list are freed
// before the copy is made.
// 
// Time complexity: O(N)
//
List& List::operator=(const List& other)
{
   if (this == &other)  // special case: check for L = L;
      return *this;     // do nothing and just return THIS object back

   //
   // This is different from a copy constructor, because "this" list
   // exists and contains nodes.  So we have to free "this" list before
   // we copy the "other" list:
   //
   this->freeAndReset();
   this->initAndDeepCopy(other);

   return *this;  // done, return THIS object back
}

//
// size
//
// Returns the # of elements in the list.
//
// Time complexity: O(1)
//
int List::size()
{
   //
   // TODO:
   //
   return this->Count;
}

//
// empty
//
// Returns true if empty, false if not.
//
// Time complexity: O(1)
//
bool List::empty()
{
   //
   // TODO:
   //
    
   return (this->Count == 0);
}

//
// search
//
// Search the list for the first occurence of the string value.
// If found, its position in the list is returned. Positions are 
// 0-based, meaning the first node is position 0. If the value is
// not found, -1 is returned.
//
// Time complexity: on average O(N)
//
int List::search(string value)
{
   //
   // TODO:
   //
    // where to starts the search
    Node* cur = this->Head;
    int i = 0;
    
    // searching the list
    while (cur != nullptr) {
        
        if (cur->Data.Value1 == value) {
            return i;
        }
        
        i++; 
        cur = cur->Next; 
    }
    // if not found return -1
    return -1; 

}

//
// retrieve
//
// Retrieve's the data from node at the given position; the list 
// remains unchanged. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("List::retrieve: invalid position");
//
// Time complexity: on average O(N)
//
void List::retrieve(int pos, string& value1, int& value2)
{
   //
   // TODO:
   //
    Node* cur = this->Head;
    
    if(pos < 0) { 
         throw invalid_argument("List::retrieve: invalid position");
    }
    
    while(cur != nullptr) {
        
        // if we get to 0, this is where we retrieve/copy
        if(pos == 0) { // node found
            value1 = cur->Data.Value1;
            value2 = cur->Data.Value2;
            return;
        }
        
        //decrement the position til pos == 0
        pos--; 
        
        //go to next node
        cur = cur->Next;
    }
    
    // if pos was greater than the size of list
    throw invalid_argument("List::retrieve: invalid position");
    
   
}

//
// insert
//
// Inserts the given data in the list such that after
// the insertion, the value is now at the given
// position.
//
// Positions are 0-based, which means a position of 0 
// denotes the data will end up at the head of the list,
// and a position of N (where N = the size of the list)
// denotes the data will end up at the tail of the list.
// If the position is invalid, throws an exception, i.e.
// throw invalid_argument("List::insert: invalid position");
//
// Time complexity: on average O(N)
//
void List::insert(int pos, string value1, int value2)
{
   //
   // TODO:
   //
    
    
    // used to traverse the list
    Node* cur = this->Head;
    Node* prev = nullptr;
    if(pos < 0) { // invalid pos
         throw invalid_argument("List::insert: invalid position");
    }
    
    while(cur != nullptr) {

        //if we get to 0, this is where we want to insert
        if(pos == 0) {
            break;
        }

        //decrement the position, until we get to 0
        pos--; 

        //go to next node and increment both prev and cur
        prev = cur; 
        cur = cur->Next;
    }
    
    //if position is more than 0, that means its past the index/not found
    if(pos > 0) { 
         throw invalid_argument("List::insert: invalid position");
    }
     
    // now we insert the node
    
    // making the new node 
    Node* newN = new Node();
    newN->Data.Value1 = value1;
    newN->Data.Value2 = value2;
    newN->Next = nullptr;
    
    //if we need to insert at the head
    if (prev == nullptr){
        
        //head insertion
        newN->Next = this->Head;
        this->Head = newN;
        
        //if tail is empty, that means we can initialize it
        if(this->Tail == nullptr){
            this -> Tail = newN;
        } 
        
    }
    
    else { //between some prev/cur
        
        //swaps and insert
        prev->Next = newN;
        newN->Next = cur;
        
        //if cur is empty, that means we are at the end of the list
        if(cur == nullptr){
            this -> Tail = newN;
        } 
    }
    
    //increment the count because we just added something
    this->Count++; 

}

//
// remove
//
// Removes and deletes the node at the given position; no data is
// returned. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("List::remove: invalid position");
//
// Time complexity: on average O(N)
//
void List::remove(int pos)
{
   //
   // TODO:
   //
    
    // used to navigate the list
    Node* cur = this->Head;
    Node* prev = nullptr;
    
    if (pos < 0) { 
         throw invalid_argument("List::remove: invalid position");
    }
    
    //all this loop does it get to where we want to remove
    while (cur != nullptr) {

        
        if (pos == 0) { // we've hit where we wanna insert
            break;
        }

        //decrement the position, until we get to 0
        pos--; 

        //go to next node and move both prev and cur
        prev = cur; 
        cur = cur->Next;
    }

    if (cur != nullptr) {
        //if pos == 0, remove the head
        if (prev == nullptr) {
            this->Head = cur->Next; 
        }
        
        else { // pos is not head
            //remove cur
            prev->Next = cur->Next;
        }

        //checks if tail the current node
        if (this->Tail == cur) {
            this->Tail = prev; 
        }

        //officially delete cur
        delete cur; 

        //decrement the count because we just removed something
        this->Count--;
        
        return;
    }
    
    throw invalid_argument("List::remove: invalid position");
}

//
// front
//
// Returns the data from the first node in the list. Throws an 
// exception if the list is empty, i.e.
// throw runtime_error("List::front: empty list");
// 
// Time complexity: O(1)
//
void List::front(string& value1, int& value2)
{
   //
   // TODO:
   //
   if (this->Head == nullptr) { // list empty, no thoughts, head empty 
       throw runtime_error("List::front: empty list");
   } else { // list not empty
       // returning the vals for head
       value1 = this->Head->Data.Value1;
       value2 = this->Head->Data.Value2;
   }
}

//
// back
//
// Returns the data from the last node in the list. Throws an 
// exception if the list is empty, i.e.
// throw runtime_error("List::back: empty list");
// 
// Time complexity: O(1)
//
void List::back(string& value1, int& value2)
{
   //
   // TODO:
   //
    if (this->Tail == nullptr) { // tail empty, list empty
       throw runtime_error("List::back: empty list");
   } else { // not empty, returning the vals for Tail
       value1 = this->Tail->Data.Value1;
       value2 = this->Tail->Data.Value2;
   }
}

//
// push_front
//
// Inserts the given data at the front of the list.
// 
// Time complexity: O(1)
//
void List::push_front(string value1, int value2)
{
   //
   // TODO:
   //
    
    // making the new node
    Node* newN = new Node();

    newN->Data.Value1 = value1;
    newN->Data.Value2 = value2;
    newN->Next = nullptr; 
    
    
    // if head is empty
    if (this->Head == nullptr) {
        
        // nothing in there, so both are going to be newN
        this->Head = newN;
        this->Tail = newN;
    }
    
    else { // head not empty
        
        //the next will be the old head
        newN->Next = this->Head;
        //then adjust the new head
        this->Head = newN;
    }
    
    this->Count++; 
    
   
}

//
// push_back
//
// Inserts the given data at the back of the list.
// 
// Time complexity: O(1)
//
void List::push_back(string value1, int value2)
{
   //
   // TODO:
   //
    
    //make a new node
    Node* newN = new Node();

    newN->Data.Value1 = value1;
    newN->Data.Value2 = value2;
    newN->Next = nullptr; 
    
    
    // if tail is empty
    if (this->Tail == nullptr) {
        
        //nothing in there, so both are going to be newN
        this->Head = newN;
        this->Tail = newN;
    }
    
    else { // tail not empty
        
        //set the next of the old tail to be the current tail
        //then adjust the new tail
        this->Tail->Next = newN; 
        this->Tail = newN;
    }
    
    this->Count++; 
}
