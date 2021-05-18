//
// Author: Sydney Wells, UIC, Spring 2021
// Assignment: Project 1: Part 2
//

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

// max val function! status: working fine!
double MaxBal(double b1, double b2, double b3, double b4, double b5) {
    double max;
    max = 0;
    
    if ((b1 > b2) && (b1 > b3) && (b1 > b4) && (b1 > b5)) {
        max = b1;
    } else if ((b2> b1) && (b2 > b3) && (b2 > b4) && (b2 > b5)) {
        max = b2;
    } else if ((b3 > b1) && (b3 > b2) && (b3 > b4) && (b3 > b5)) {
        max = b3;
    } else if ((b4 > b1) && (b4 > b2) && (b4 > b3) && (b4 > b5)) {
        max = b4;
    } else if ((b5 > b1) && (b5 > b2) && (b5 > b3) && (b5 > b4)) {
        max = b5;
    }
    
    return max;
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
    
    // accounts n balances
    int account1;
    double bal1;

    int account2;
    double bal2;

    int account3;
    double bal3;

    int account4;
    double bal4;

    int account5;
    double bal5;

    // variables for commands
    double dep;
    double wd;
    double mv;
    
    // welcome text and getting bank file
    cout << "** Welcome to UIC Bank v1.0 **" << endl << "Enter bank filename> " << endl;
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


    // getting account numbers and balances from input file
    infile >> account1;
    infile >> bal1;
    infile >> account2;
    infile >> bal2;
    infile >> account3;
    infile >> bal3;
    infile >> account4;
    infile >> bal4;
    infile >> account5;
    infile >> bal5;
    
    infile.close();
    
    // outputting account numbers and balances
    cout << "** Outputting account data..." << endl;
    cout << "Account " << account1 << ": balance $" << bal1 << endl;
    cout << "Account " << account2 << ": balance $" << bal2 << endl;
    cout << "Account " << account3 << ": balance $" << bal3 << endl;
    cout << "Account " << account4 << ": balance $" << bal4 << endl;
    cout << "Account " << account5 << ": balance $" << bal5 << endl;

    cout << "** Processing user commands..." << endl;
    cout << "Enter command (+, -, ?, ^, *, x): " << endl;
    cin >> command;

    // while loop
    while (command != "x") {
        
         if (command == "+") {
            cin >> actnum;
            cin >> dep;
            if ((actnum != account1) && (actnum != account2) && (actnum != account3) && (actnum != account4) && (actnum != account5)) {
                cout << "** Invalid account, transaction ignored" << endl;   
            } else if (actnum == account1) {
            bal1 = bal1 + dep;
            cout << "Account " << account1 << ": balance $" << bal1 << endl;
            } else if (actnum == account2) {
            bal2 = bal2 + dep;
            cout << "Account " << account2 << ": balance $" << bal2 << endl;
            } else if (actnum == account3) {
            bal3 = bal3 + dep;
            cout << "Account " << account3 << ": balance $" << bal3 << endl;
            } else if (actnum == account4) {
            bal4 = bal4 + dep;
            cout << "Account " << account4 << ": balance $" << bal4 << endl;
            } else if (actnum == account5) {
            bal5 = bal5 + dep;
            cout << "Account " << account5 << ": balance $" << bal5 << endl;
            }

        // - branch
        } else if (command == "-") {
            cin >> actnum;
            cin >> wd;
            if ((actnum != account1) && (actnum != account2) && (actnum != account3) && (actnum != account4) && (actnum != account5)) {
                cout << "** Invalid account, transaction ignored" << endl;
            } else if (actnum == account1) {
                bal1 = bal1 - wd;
                cout << "Account " << account1 << ": balance $" << bal1 << endl;
            } else if (actnum == account2) {
                bal2 = bal2 - wd;
                cout << "Account " << account2 << ": balance $" << bal2 << endl;
            } else if (actnum == account3) {
                bal3 = bal3 - wd;
                cout << "Account " << account3 << ": balance $" << bal3 << endl;
            } else if (actnum == account4) {
                bal4 = bal4 - wd;
                cout << "Account " << account4 << ": balance $" << bal4 << endl;
            } else if (actnum == account5) {
                bal5 = bal5 - wd;
                cout << "Account " << account5 << ": balance $" << bal5 << endl;
            }

        // ? branch
        } else if (command == "?") {
            cin >> actnum;
            if ((actnum != account1) && (actnum != account2) && (actnum != account3) && (actnum != account4) && (actnum != account5)) {
                cout << "** Invalid account, transaction ignored" << endl;
            } else if (actnum == account1) {
                cout << "Account " << account1 << ": balance $" << bal1 << endl;
            } else if (actnum == account2) {
                cout << "Account " << account2 << ": balance $" << bal2 << endl;
            } else if (actnum == account3) {
                cout << "Account " << account3 << ": balance $" << bal3 << endl;
            } else if (actnum == account4) {
                cout << "Account " << account4 << ": balance $" << bal4 << endl;
            } else if (actnum == account5) {
                cout << "Account " << account5 << ": balance $" << bal5 << endl;
            }  

        // ^ branch 
        } else if (command == "^") {
            mv = MaxBal(bal1, bal2, bal3, bal4, bal5);
            if (mv == bal1) {
                cout << "Account " << account1 << ": balance $" << bal1 << endl;
            } else if (mv == bal2) {
                cout << "Account " << account2 << ": balance $" << bal2 << endl;
            } else if (mv == bal3) {
                cout << "Account " << account3 << ": balance $" << bal3 << endl;
            } else if (mv == bal4) {
                cout << "Account " << account4 << ": balance $" << bal4 << endl;
            } else if (mv == bal5) {
                cout << "Account " << account5 << ": balance $" << bal5 << endl;
            }

        // * branch    
        } else if (command == "*") {
            cout << "Account " << account1 << ": balance $" << bal1 << endl;
            cout << "Account " << account2 << ": balance $" << bal2 << endl;
            cout << "Account " << account3 << ": balance $" << bal3 << endl;
            cout << "Account " << account4 << ": balance $" << bal4 << endl;
            cout << "Account " << account5 << ": balance $" << bal5 << endl;
        
        // invalid command     
        } else {
             cout << "** Invalid command, try again..." << endl;
        } // end of branches
        
        cout << "Enter command (+, -, ?, ^, *, x): " << endl;
        cin >> command;
    } // end of while

    
    // updating bank file
    cout << "** Saving account data..." << endl;
    
    outfile.open(ouf);
    outfile << account1 << " " << bal1 << endl;
    outfile << account2 << " " << bal2 << endl;
    outfile << account3 << " " << bal3 << endl;
    outfile << account4 << " " << bal4 << endl;
    outfile << account5 << " " << bal5 << endl;
    outfile.close();
    
    // all done!
    cout << "** Done **" << endl;

    return 0;
} // end of file

