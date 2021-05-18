// Author: Sydney Wells, UIC, Spring 2021
// Assignment: Project 5, Part 2
// Description: Program that creates and manipulates linked lists

#include "list.h"
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;


// 
// init_list
//
// Initializes list to empty; must be called before list can 
// be used with other functions.
//
void init_list(List& L) {
    // sets head to nullptr since 
    // there's nothing to point to yet
    // and count to 0 since the list
    // is empty
    L.Head = nullptr;
    L.Count = 0;
}

//
// print_list
//
// Outputs "List: " followed by each data element and a space. Output
// is directed to the console. The format of each data element is 
// (field1,field2,...), e.g. (ID,Priority).
//
void print_list(List L) {
    // traversing the list and printing id
    // and priority of each item in the list
    Node* cur = L.Head;
    int i = 0;
    cout << "List: ";
    if (L.Count == 0) {
        cout << endl;
    } else {
        while ((i < L.Count) && (cur != nullptr)) {
            cout << "(" << cur->Data.ID << "," << cur->Data.Priority << ") ";
            cur = cur->Next;
            i++;
        }
        cout << endl;
    }
    
}

//
// push_back_list
//
// Pushes the data onto the end of the list.
//
void push_back_list(List& L, NodeData d) {
    // make a new node and initialize the values
    Node* newN = new Node();
    newN->Data = d;
    newN->Next = nullptr;
    
    Node* cur = L.Head;
    
    // checks if the list is empty
    // or not, if it is, then the head
    // is set to newN, and if not, we
    // traverse the list until we reach 
    // the end. whether or not the list 
    // is empty, L.Count increases by 1
    if (L.Count == 0) {
        L.Head = newN;
        L.Count++;
    } else {
        while (cur->Next != nullptr) {
            cur = cur->Next;
        }
        cur->Next = newN;
        L.Count++;
    }

}

//
// push_front_list
//
// Pushes the data onto the front of the list.
//
void push_front_list(List& L, NodeData d) {
    //assign the new node's value and pointer
    Node* newN = new Node();
    newN->Data = d;
    newN->Next = L.Head;
    
    // make the new node the head of 
    // the list and increase the count
    L.Head = newN;
    L.Count++;
}

//
// free_list
//
// Deletes all nodes from the list, frees the memory, and resets
// the list to empty.
//
void free_list(List& L) {
    Node* cur = L.Head;
    
    while (cur != nullptr) {
        
        Node* temp = cur;
        cur = cur->Next;
        delete temp;
    }

    init_list(L);

}

//
// search_list
//
// Search the list for the first occurrence of the given ID. If found,
// its position in the list is returned; positions are 0-based,
// meaning the first node is position 0. If not found, -1 is
// returned.
//
int search_list(List L, int ID) {
    Node* cur = L.Head;
    int i = 0;
   // searching the list
    while ((i <= (L.Count - 1) && (cur->Data.ID != ID))) {
        cur = cur->Next;
        i++;
    }
   // if not found, return -1
    if (i > (L.Count - 1)) {
        i = -1;
    }
    return i;
}

//
// retrieve_from_list
//
// Retrieve's the data from node at the given position; the list 
// remains unchanged. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("retrieve_from_list: invalid position");
//
NodeData retrieve_from_list(List L, int pos) {
    Node* cur = L.Head;
    int i = 0;
    int j = L.Count - 1;
   
    //making sure position is valid
    // if it isnt, the invalid_argument
    // is thrown, else, searches the list
    // until the proper node is found
    if ((pos < 0) || (pos > j)) {
        throw invalid_argument("retrieve_from_list: invalid position");
    } else {
        while (i != pos) {
            cur = cur->Next;
            i++;
        }
    }
    return cur->Data;
}

//
// remove_from_list
//
// Removes and frees the node at the given position, returning 
// the node's data. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("remove_from_list: invalid position");
//
NodeData remove_from_list(List& L, int pos) {
    Node* cur = L.Head;
    Node* prev = nullptr;
    int i = 0;
    int j = L.Count - 1;
    
    // make sure the pos is valid
    if ((pos < 0) || (pos > j)) {
        throw invalid_argument("remove_from_list: invalid position");
    // searches for the element we want
    } else {
        //L.Count--;
        while (cur != nullptr) {
            if (i == pos) {
                break;
            }
            prev = cur;
            cur = cur->Next;
            i++;
        }
        // check if prev is nullptr
        // if so dont use prev->Next = cur->Next
        L.Count--;
        NodeData d;
        if (prev == nullptr) {
            prev = cur;
            d = prev->Data;
            cur = cur->Next;
            L.Head = cur;
            delete prev;
            return d;
            
            //L.Count--;
        } else {
            // is cur null? is that the issue??
            prev->Next = cur->Next;
            d = cur->Data;
            delete cur;
            return d;
            
        }

    }
    
       
    
}
