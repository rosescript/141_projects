// Author: Sydney Wells, UIC, Spring 2021
// Assignment: Project 5, Part 2
// Description: Program that creates and manipulates linked lists
// this is really just a test file

#include "list.h"
#include "pqueue.h"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
#include <cctype>
#include <exception>
#include <stdexcept>

using namespace std;


int main() {
    List L;
    
    init_list(L);
    pq_enqueue(L, 21, 9);
    pq_enqueue(L, 19, 1);
    pq_enqueue(L, 9, 12);
    pq_enqueue(L, 13, 6);
    pq_enqueue(L, 18, 6);
    pq_enqueue(L, 283, 3);
    
    /*string filename;
    cout << "Please enter a filename> " << endl;
    cin >> filename;
    
    // open the file, check if it's good
    ifstream infile;
    infile.open(filename);
    
    if (!infile.good()) {
        cout << "Error opening file '" << filename << "'. Goodbye." << endl;
        return 0;
    }
    
    // put the file contents into our linked list
    NodeData x;
    
    //infile >> x.ID;
    //infile >> x.Priority;
    
    while(!infile.eof()) {
        infile >> x.ID;
        infile >> x.Priority;
        push_back_list(L,x);
    }
    infile >> x.ID;
    infile >> x.Priority;
    push_back_list(L,x);
    
    //L.Count--;
    
    cout << L.Count << endl;
    print_list(L);
    
    int h = search_list(L, 200);
    cout << h << endl;
    
    NodeData buh = retrieve_from_list(L, 1);
    cout << buh.ID << endl;*/
    
    //NodeData i, j, k;
    
    /*i.ID = 23;
    i.Priority = 2;
    push_back_list(L, i);
    
    j.ID = 37;
    j.Priority = 8;
    push_back_list(L, j);
    
    k.ID = 6;
    k.Priority = 89;
    push_back_list(L, k);*/
    
    int m = search_list(L, 1);
    
    cout << m << endl;
    
    
    
    print_list(L);
    
    m = search_list(L, 19);
    cout << m << endl;
    cout << L.Count << endl;
    
    print_list(L);
    
    //pq_front(L);
    //cout << buh << endl;
    
    //NodeData p = retrieve_from_list(L, 99);
    
    //cout << p.ID << endl;
    
    //NodeData p = remove_from_list(L, 1);
    
    //cout << p.ID << endl;
    int p = pq_front(L);
    cout << p << endl;
    pq_enqueue(L, 75, 100);
    pq_nudge(L, 18);
    pq_enqueue(L, 38, 100);
    print_list(L);
    List M;
    init_list(M);
    pq_enqueue(M,1, 12);
    M = L;
    cout << "L Count: " << L.Count << endl;
    cout << "M Count: " << M.Count << endl;
    
    p = pq_front(L);
    cout << p << endl;
    
    remove_from_list(L, 0);
    
    
    cout << L.Count << endl;
    
    
    //List M = pq_duplicate(L);
    
    
    
    /*print_list(M);
    pq_dequeue(M);
    print_list(M);*/
    
    
    print_list(L);
    cout << L.Count << endl;
    
    //cout << p.ID << endl;
    
    
    
    free_list(L);
    free_list(M);
    
    print_list(L);
    //cout << L.Count << endl;
    
   
    
    
    
    
    return 0;
}
