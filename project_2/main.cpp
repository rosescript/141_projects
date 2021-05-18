//
// Author: Sydney Wells, UIC, Spring 2021
// Assignment: Project 2: Part 2
//

//
// this program emulates a bank. you can deposit or withdraw to
// accounts, check account info, figure out the account with the
// most money, etc. part 1 of this project is having us create a
// couple of functions and adapt the program to deal with arrays
// instead of a set number of accounts and balances
// part 2 is adding some more command functionality
// including adding and deleting accounts
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// max balance function! status: fully operational!
// given a number of balances, this function returns the largest one
// FIXME: adapt it so it works w/ arrays (done!)
int maxBalance(double balances[], int N)
{
    double max;
    int maxindex;
    maxindex = 0;
    max = balances[0];

    for (int i = 0; i < N; i++) {
        if (balances[i] > max) {
            max = balances[i];
            maxindex = i;
        }
    }
    return maxindex; // gives the index of that particular account and balance
    // also maybe try return i-1?
    // because see the value of max doesnt matter so much as
    // the index of the balance bc thats what we need to get to the
    // account connected with it!
    // ^ dont do that b
    // update (2:37 am 2/3/21): soooo this only works if you return (i-1) rn
    // (i+1) and i get valgrind errors and it sets the account and
    // balance to 0???? also only gives the largest account number not
    // the largest balance
    // update (1:51 pm 2/3/21): fixed!
}


//
// checkArrays
// Required function that currently outputs to console, but when submitted
// to gradescope this function will be replaced by one that performs more
// extensive checks to make sure the data was input correctly.
// status: fully operational!
//
void checkArrays(int accounts[], double balances[], int N)
{
    cout << std::fixed;
    cout << std::setprecision(2);

    cout << "** Checking arrays..." << endl;
    cout << "1. " << accounts[0] << ", $" << balances[0] << endl;
    cout << N << ". " << accounts[N-1] << ", $" << balances[N-1] << endl;
}

//
// search
//
// Given an array of N accounts in ascending order, searches for
// the account that matches "acct". If found, the index of that
//account is returned; if not found -1 is returned.
// status: fully operational!
//
int search(int accounts[], int N, int acct)
{
    //lab 04 has a *very* similar function!
    int ind = 0;
    int i = 0;
    
    /*for (int i = 0; i < N; i++) {
        if (accounts[i] == acct) {
            ind = i;
        }
    }*/

   while ((i < N) && (ind < 1)) {
       if (accounts[i] == acct) {
           ++ind;     
       }
       i++;
       
   }
    if (ind == 1) {
        return (i-1);
    } else {
        return -1;
    }
}

int main()
{
    cout << std::fixed;
    cout << std::setprecision(2);

    // declaring variables
    ifstream infile;
    ofstream outfile;

    string inf;
    string ouf;
    string command;
    int actnum;

    // variables for commands
    double dep;
    double wd;
    int index;

    // N (array size)
    int N = 0;
    
    //array pointers
    int* accounts;
    double* balances;

    // welcome text and getting bank file
    cout << "** Welcome to UIC Bank v2.0 **" << endl << "Enter bank filename> " << endl;
    cin >> inf;
    ouf = inf;
    cout << "** Inputting account data..." << endl;

    // making sure file is good
    infile.open(inf);
    if (!infile.good())
      {
         cout << endl << "**Error: unable to open input file '" << inf << "'" << endl;
         return 0;
      }

    // gets the num of accounts n balances
    infile >> N;

    // creating the arrays
    
    accounts = new int[N];
    balances = new double[N];
    
    // getting account numbers and balances from input file
    // FIXME: gotta change this to a for loop that sends these to
    // their respective arrays (accounts & balances) (DONE)

    for (int i = 0; i < N; ++i) {
        infile >> accounts[i];
        infile >> balances[i];
    }

    infile.close();
    
    // calling checkArrays
    checkArrays(accounts, balances, N);

    // processing user commands n asking user for a command
    cout << "** Processing user commands..." << endl;
    cout << "Enter command (+, -, ?, ^, *, <, $, add, del, x): " << endl;
    cin >> command;

    // while loop (processes the bank commands and performs 
    // actions based off of said command)
    while (command != "x") {
        
        // + branch:
        // deposits money into an account
         if (command == "+") {
            cin >> actnum;
            cin >> dep;
            index = search(accounts, N, actnum);
            if (index == -1) {
                cout << "** Invalid account, transaction ignored" << endl;
            } else {
                balances[index] = balances[index] + dep;
                cout << "Account " << accounts[index] << ": balance $" << balances[index] << endl;
            }

        // - branch:
        // withdraws money from an account
        } else if (command == "-") {
            cin >> actnum;
            cin >> wd;
            index = search(accounts, N, actnum);
            if (index == -1) {
                cout << "** Invalid account, transaction ignored" << endl;
            } else {
                balances[index] = balances[index] - wd;
                cout << "Account " << accounts[index] << ": balance $" << balances[index] << endl;
            }

        // ? branch:
        // displays the current balance of a given account
        } else if (command == "?") {
            cin >> actnum;
            index = search(accounts, N, actnum);
            if (index == -1) {
                cout << "** Invalid account, transaction ignored" << endl;
            } else {
                cout << "Account " << accounts[index] << ": balance $" << balances[index] << endl;
            }

        // ^ branch:
        // displays the account with the largest balance
        // rn its displaying like, the largest account number, not the account
        // w/ the largest balance and i am confusion
        // its now working nvm
        } else if (command == "^") {
            index = maxBalance(balances, N);
            cout << "Account " << accounts[index] << ": balance $" << balances[index] << endl;

        // * branch:
        // displays all accounts from low to high within a given range
        } else if (command == "*") {
            // these two vars are specifically for the * function
            int low = 0;
            int high = 0;
            cin >> low;
            cin >> high;
            int k = 0;
            int inaccounts = 0;
            k = low;
           while (k <= high) {
                inaccounts = search(accounts, N, k);
                if (inaccounts != -1) {
                    cout << "Account " << accounts[inaccounts] << ": balance $" << balances[inaccounts] << endl;
                }
                ++k;
            } 
            
        // < branch:
        // displays all accounts with a negative balance
        } else if (command == "<") {
            for (int i = 0; i < N; ++i) {
                if (balances[i] < 0) {
                    cout << "Account " << accounts[i] << ": balance $" << balances[i] << endl;
                }
            }
             
        // $ branch:
        // adds all accounts with a positive balance together
        // and displays the total
        } else if (command == "$") {
             double ptotal = 0.0;
             for (int i = 0; i < N; ++i) {
                 if (balances[i] >= 0.0) {
                     ptotal = ptotal + balances[i];
                 }
             }
             cout << "Total deposits: $" << ptotal << endl;
             
        // add branch:
        // adds a new account to the list of accounts
        // also makes a new list to accomodate the new account
        } else if (command == "add") {
             // takes the max account num and adds 1 to make
             // a new account
             int nAcctNum = accounts[N-1] + 1;
             
             // new array pointers
             int* tempA = new int[N+1];
             double* tempB = new double[N+1];
             
             // copying the accounts to new array
             for (int i = 0; i < N; ++i) {
                 tempA[i] = accounts[i];
             }
             // adding the new account in 
             tempA[N] = nAcctNum;
             
             // copying the balances to new array
             for (int i = 0; i < N; ++i) {
                 tempB[i] = balances[i];
             }
             // adding new balance in
             tempB[N] = 0.0;            
             
             // deleting old arrays
             delete[] accounts;
             delete[] balances;
             
             // setting pointers to new lists
             accounts = tempA;
             balances = tempB;
             
             // increasing N
             N = N + 1;
             
             // outputting the new account
             cout << "Added account " << accounts[N-1] << ": balance $" << balances[N-1] << endl;
             
             // cout << N; <-- making sure N got updated
             /* for (int i = 0; i < N; i++) {
                 cout << "Account " << accounts[i] << ": balance $" << balances[i] << endl;
             } <-- making sure the list was properly updated*/
             
             // it works now omg
             
        // del branch:
        // deletes a given account from the file
        } else if (command == "del") {
             cin >> actnum;
             index = search(accounts, N, actnum);
             for (int i = index; i < N; i++) {
                 accounts[i] = accounts[i + 1];
             }
             accounts[N-1] = {};
             
             for(int i = index; i < N; i++) {
                 balances[i] = balances[i + 1];
             }
             balances[N-1] = {};
             
             /* for (int i = 0; i < N; ++i) {
                 cout << "Account " << accounts[i] << ": balance $" << balances[i] << endl;
             } <-- making sure list came out right */
             cout << "Deleted account " << actnum << endl; 
             
        // invalid command branch     
        } else {
             cout << "** Invalid command, try again..." << endl;
        } // end of branches

        cout << "Enter command (+, -, ?, ^, *, <, $, add, del, x): " << endl;
        cin >> command;
    } // end of while


    // updating bank file
    cout << "** Saving account data..." << endl;

    outfile.open(ouf);
    outfile << std::fixed;
    outfile << std::setprecision(2);

    // FIXME: needs to be turned into a for loop (DONE)
    outfile << N << endl;

    for (int i = 0; i < N; i++) {
        outfile << accounts[i] << " " << balances[i] << endl;
    }
    
    outfile.close();

    // all done!
    cout << "** Done **" << endl;

    // get rid of those lil arrays n we'll be on our way
    
    delete[] accounts;
    delete[] balances;
    

    return 0;
} // end of file
