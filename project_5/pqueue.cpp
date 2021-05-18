// Author: Sydney Wells, UIC, Spring 2021
// Assignment: Project 5, Part 2
// Description: Program that creates and manipulates linked lists

#include "list.h"
#include "pqueue.h"
#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

using namespace std;


//
// pq_init
//
// Initializes list to empty; must be called before list can 
// be used with other queue functions.
//
void pq_init(List& L) {
    // sets head to nullptr since 
    // there's nothing to point to yet
    // and count to 0 since the list
    // is empty
    init_list(L);
}

//
// pq_print
// 
// Outputs "List: " followed by each data element and a space. Output
// is directed to the console. The format of each data element is 
// (field1,field2,...), e.g. (ID,Priority).
//
void pq_print(List L) {
    // it print
    print_list(L);
}

//
// pq_front
//
// Returns the ID at the front of the priority queue. Throws 
// an "invalid_argument" exception if the queue is empty, i.e.
// throw invalid_argument("pq_front: queue empty");
//
int pq_front(List L) {
    Node* cur = L.Head;
    // check if list is empty,
    // if not return the first element's ID
    if (L.Head == nullptr) {
        throw invalid_argument("pq_front: queue empty");
    } else {
        return cur->Data.ID;
    }
}

//
// pq_dequeue
//
// Removes the data element at the front of the queue, removing the
// node as well and freeing this memory. Nothing is returned.
// Throws an "invalid_argument" exception if the queue is empty, i.e.
// throw invalid_argument("pq_dequeue: queue empty");
//
void pq_dequeue(List& L) {
    
    if (L.Head == nullptr) {
        throw invalid_argument("pq_dequeue: queue empty");
    } else {
        // removes the head of the list!
        remove_from_list(L,0);
    }
}

//
// pq_enqueue
//
// Inserts the given (ID,priority) pair into the queue based on
// the priority, ordered low to high. If elements already exist with
// the same priority, this new element comes after those elements.
// Example: suppose the queue currently contains the following 
// (ID,Priority) pairs:
// 
//   (10,19) (84,25) (21,50)
//
// A call to enqueue (79,25) yields the following result:
//
//   (10,19) (84,25) (79,25) (21,50)
//
// If the ID is already in the queue, then the pair is repositioned 
// based on the new priority. For example, suppose the queue is as
// shown above, and we enqueue (84,50). The result is now
//
//   (10,19) (79,25) (21,50) (84,50)
//
void pq_enqueue(List& L, int ID, int priority) {
    int index = search_list(L, ID);
    // check if ID is in list, if so delete that node
    if (index != -1) {
        remove_from_list(L, index);
    }
    // make a new node!
    Node* newN = new Node();
    newN->Data.ID = ID;
    newN->Data.Priority = priority;
    newN->Next = nullptr;
    //increase the count!
    L.Count++;
    // check if list is empty
    // if empty, just set head = to newN
    // else search for insertion point, 
    // then pop that bad boy in there
    if (L.Head == nullptr) {
        L.Head = newN;
    } else {
        Node* cur = L.Head;
        Node* prev = nullptr;
        while (cur != nullptr) {
            if (cur->Data.Priority > newN->Data.Priority) {
                break;
            }
            prev = cur;
            cur = cur->Next;
        }
        if (prev == nullptr) {
            newN->Next = L.Head;
            L.Head = newN;
        } else {
            prev->Next = newN;
            newN->Next = cur;
        }
    }
    
    
}

//
// pq_nudge
// 
// Nudges the element with the given ID forward one element in the
// queue. The element takes on the same priority as the element
// that now follows it.  Example: suppose the queue currently contains
// the following (ID,Priority) pairs:
// 
//   (10,19) (84,25) (21,50)
//
// A call to "nudge" 21 forward produces this result:
//
//   (10,19) (21,25) (84,25)
//
// If the ID is already at the front of the queue, nothing happens.
// If the ID is not in the queue, throws "invalid_argument" exception, i.e.
// throw invalid_argument("pq_nudge: ID not found");
//
void pq_nudge(List& L, int ID) {
    int index = search_list(L, ID);
    Node* cur = L.Head;
    Node* prev = nullptr;
    int i = 0;
    if (index == -1) {
        throw invalid_argument("pq_nudge: ID not found");
    } else {
        if (cur->Data.ID == ID) {
            return;
        } else {
            
            // have a prev and a cur and make cur stop at the node ID tha the user entered
            
            while (cur->Data.ID != ID) {
                prev = cur;
                cur = cur->Next;
                i++;
            }
            
            
            // swap the IDs of cur and prev and then
            // make both prev's and cur's priorities equal
            
            if (L.Count == 2) {
                cur->Next = prev;
                L.Head = cur;
            //swap them vals    
            } else {
                int l = prev->Data.ID;
                int m = cur->Data.ID;
                cur->Data.Priority = prev->Data.Priority;
                cur->Data.ID = l;
                prev->Data.ID = m;
            }
            
        }
    }
}

//
// pq_clear
//
// Deletes all nodes from the list, frees the memory, and resets
// the list to empty.
//
void pq_clear(List& L) {
    free_list(L);
}

//
// pq_duplicate
//
// Makes a complete copy of the given list L and returns this duplicate.
// A "deep" copy is made, meaning all nodes and data are duplicated in 
// the new, returned list.
//
List pq_duplicate(List L) {
    List M;
    init_list(M);
    Node* cur = L.Head;
    Node* ncur = nullptr;
    M.Head = ncur;
    while (cur != nullptr) {
        ncur = cur;
        push_back_list(M, ncur->Data);
        cur = cur->Next;
    }
    return M;
}
