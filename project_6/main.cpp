//
// Author: Sydney Wells, UIC, Spring 2021
// Assignment: Project 6
// Description: Class registration system
// that enrolls and waitlists students, as
// well as processes command files. it can 
// also increase class sizes, output the
// current total of enrolled and waitlisted
// students for all classes or list the enrollment
// data for a specific class.
//

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include "classreg.h"


using namespace std;


//
// help:
// outputs all available commands (minus help!)
//

void help() {
    cout << "stats" << endl << "list class" << endl << "increase class capacity" << endl << "enroll class netid" << endl;
    cout << "waitlist class netid priority" << endl << "process filename" << endl << "output filename" << endl << "quit" << endl;
}

//
// stats:
// outputs the num of enrolled and waitlisted
// students for each class
//

void stats(ClassReg classes[]) {
    // looping through and printing the desired info
    for (int i = 0; i < 5; i++) {
        cout << classes[i].getName() << ": enrolled=" << classes[i].numEnrolled() << ", waitlisted=" << classes[i].numWaitlisted() << endl;
    }
}

//
// sortByName:
// sorts an array of strings alphabetically
//

void sortByName(string netids[], int numNetids)
{
    // looping through the array
    for (int i = 0; i < numNetids-1; i++)
   {
      int minIndex = i;
      //comparing netids
      for (int j = i+1; j < numNetids; j++)
      {
         if (netids[j] < netids[minIndex])
         {
            minIndex = j;
         }
      }
      //sorting netids
      string temp = netids[i];
      netids[i] = netids[minIndex];
      netids[minIndex] = temp;
   }
    // outputting the sorted netids
    for (int i = 0; i < numNetids; i++) {
        cout << netids[i] << " ";
    }
}

//
// output:
// takes the current enrollment data and outputs it
// into a given filename
//

void output(string filename, ClassReg classes[]) {
    ofstream outfile;
    ifstream infile;
    infile.open(filename);
    if (!infile.good()) { // if file doesn't exist yet
        // creating the new file
        ofstream newFile(filename);
    
        // looping through each class
        for (int i = 0; i < 5; i++) {
        
            // entering name and capacity
            newFile << classes[i].getName() << endl;
            newFile << classes[i].getCapacity() << endl;
        
            // checks to see if anyone is enrolled, 
            // if so enters those names into the file
            if (classes[i].numEnrolled() == 0) {
                newFile << "#" << endl;
            } else {
                for (int j = 0; j < classes[i].numEnrolled(); j++) {
                    newFile << classes[i].retrieveEnrolledStudent(j) << " ";
                }
                newFile << "#" << endl;
            }
        
            // checks to see if anyone is waitlisted, 
            // if so enters those names into the file
            if (classes[i].numWaitlisted() == 0) {
                newFile << "#" << endl;
            } else {
                string id;
                int priority;
                for (int h = 0; h < classes[i].numWaitlisted(); h++) {
                    classes[i].retrieveWaitlistedStudent(h, id, priority);
                    newFile << id << " " << priority << " ";
                }
                newFile << "#" << endl;
            }
        }
    } else {
        // file does exist, so we're gonna enter new data into it
        outfile.open(filename);
        // looping through each class
        for (int i = 0; i < 5; i++) {
        
            // entering name and capacity
            outfile << classes[i].getName() << endl;
            outfile << classes[i].getCapacity() << endl;
        
            // checks to see if anyone is enrolled, 
            // if so enters those names into the file
            if (classes[i].numEnrolled() == 0) {
                outfile << "#" << endl;
            } else {
                for (int j = 0; j < classes[i].numEnrolled(); j++) {
                    outfile << classes[i].retrieveEnrolledStudent(j) << " ";
                }
                outfile << "#" << endl;
            }
        
            // checks to see if anyone is waitlisted, 
            // if so enters those names into the file
            if (classes[i].numWaitlisted() == 0) {
                outfile << "#" << endl;
            } else {
                string id;
                int priority;
                for (int h = 0; h < classes[i].numWaitlisted(); h++) {
                    classes[i].retrieveWaitlistedStudent(h, id, priority);
                    outfile << id << " " << priority << " ";
                }
                outfile << "#" << endl;
            }
        }
        outfile.close();
    }
    // output was successful!
    cout << "Enrollment data output to '" << filename << "'" << endl;

}

//
// list class:
// outputs the info for a specific class
// enrolled students are output 
//

void listClass(string name, ClassReg classes[]) {
    int S = -1; // used to track if the class name is a valid one
    // searching for the right class
    for (int i = 0; i < 5; i++) {
        if (name == classes[i].getName()) {
            S = 0; // valid class name!
            // outputting class name and capacity
            cout << classes[i].getName() << endl;
            cout << "Capacity: " << classes[i].getCapacity() << endl;
            
            // outputting enrolled students
            cout << "Enrolled (" << classes[i].numEnrolled() << "): ";
            if (classes[i].numEnrolled() != 0) {
                // create a list of the currently enrolled netids
                string netids[classes[i].numEnrolled()];
                for (int j = 0; j < classes[i].numEnrolled(); j++) {
                    netids[j] = classes[i].retrieveEnrolledStudent(j);
                }
                // sorting the netids and outputting them alphabetically
                sortByName(netids, classes[i].numEnrolled());
            }
            cout << endl;
            
            // outputting waitlisted students
            cout << "Waitlisted (" << classes[i].numWaitlisted() << "): ";
            if (classes[i].numWaitlisted() != 0) {
                string id;
                int priority;
                for (int h = 0; h < classes[i].numWaitlisted(); h++) {
                    classes[i].retrieveWaitlistedStudent(h, id, priority);
                    cout << id << " (" << priority << ") ";
                }
            }
            cout << endl;
            
        }
    }
    // if class name is invalid
    if (S == -1) {
        cout << "**Invalid class name, try again..." << endl;
    }
}


//
// increaseCap:
// increases the class capacity to
// the requested capacity, so long
// as the requested capacity is not 
// less than or equal to the current cap
//

void increaseCap(string name, int newCap, ClassReg classes[]) {
    int S = -1; // used to track if the class name is a valid one
    // searching for the right class
    for (int i = 0; i < 5; i++) {
        if (name == classes[i].getName()) {
            S = 0; // class name is valid
            // rejects requests to decrease capacity
            if (classes[i].getCapacity() > newCap) {
                cout << "**Error, cannot decrease class capacity, ignored..." << endl;
            // else, increases the capacity
            } else {
                classes[i].setCapacity(newCap);
                cout << classes[i].getName() << endl << "Capacity: " << classes[i].getCapacity() << endl;
            }
        }
    }
    // if class name is invalid
    if (S == -1) {
        cout << "**Invalid class name, try again..." << endl;
    }
}


//
// enroll:
// enrolls a student into a class
// if the class is full, student is waitlisted
// checks to see if the student is already
// on the waitlist. if so, student is removed from
// waitlist and enrolled
//
void enroll(string name, string netid, ClassReg classes[]) {
    int S = -1; // used to check if the class name is valid
    // searching for the correct class
    for (int i = 0; i < 5; i++) {
        if (name == classes[i].getName()) {
            S = 0; // class name is valid!
            int pos = classes[i].searchEnrolled(netid);
            
            if (pos == -1) { // student not already enrolled
                if (classes[i].numEnrolled() == classes[i].getCapacity()) { // class full
                    if (classes[i].numWaitlisted() == 0) { // waitlist is empty
                        classes[i].waitlistStudent(netid, 1); // waitlists student and sets priority to 1
                        cout << "Class full, '" << netid << "' waitlisted for " << name << endl;
                    } else { // waitlist isn't empty
                        string id;
                        int priority;
                        int M = -1;
                        int pos2 = 0; // position of name if on waitlist
                        for (int j = 0; j < classes[i].numWaitlisted(); j++) {
                            classes[i].retrieveWaitlistedStudent(j, id, priority);
                            if (id == netid) {
                                M = 0;
                                break;
                            }
                            pos2++;
                        }
                        if (M == -1) { // if student not already waitlisted
                            // search for the priority of the last student on the waitlist
                            classes[i].retrieveWaitlistedStudent((classes[i].numWaitlisted()-1), id, priority);
                            classes[i].waitlistStudent(netid, priority); // waitlists student
                            cout << "Class full, '" << netid << "' waitlisted for " << name << endl;
                        } else { // student is already waitlisted
                            cout << "Class full, '" << netid << "' waitlisted for " << name << endl;
                        }
                        
                    }
                } else { // class isn't full
                    // check if student is on the waitlist
                    string id2;
                    int pri2;
                    int T = -1;
                    int pos3 = 0; // position of name if on waitlist
                    for (int h = 0; h < classes[i].numWaitlisted(); h++) {
                        classes[i].retrieveWaitlistedStudent(h, id2, pri2);
                        if (id2 == netid) {
                            T = 0;
                            break;
                        }
                        pos3++;
                    }
                    if (T == 0) { // student is on the waitlist
                        // remove from waitlist and then enroll student
                        classes[i].removeWaitlistedStudent(pos3);
                        classes[i].enrollStudent(netid);
                        cout << "Student '" << netid << "' enrolled in " << name << endl;
                    } else { // student not on waitlist
                        classes[i].enrollStudent(netid);
                        cout << "Student '" << netid << "' enrolled in " << name << endl;
                    }
                }
            } else {
                cout << "Student '" << netid << "' enrolled in " << name << endl; 
            }
            
        }
    } // end of loop
    
    if (S == -1) { // class name invalid
        cout << "**Invalid class name, try again..." << endl;
    }
}

//
// waitlist:
// waitlists a student into
// a specified class. if student
// is already enrolled in said 
// class, nothing happens
// if the student is on the 
// waitlist, they are repositioned
// if the priority is different
//

void waitlist(string name, string netid, int priority, ClassReg classes[]) {
    int S = -1; // used to check if the class name is valid
    // searching for the correct class
    for (int i = 0; i < 5; i++) {
        if (name == classes[i].getName()) {
            S = 0; // class is valid!
            int pos = classes[i].searchEnrolled(netid);
            
            if (pos == -1) {
                string id;
                int pri;
                int M = -1; // checks if student is on waitlist
                int pos2 = 0; // position of name if on waitlist
                for (int j = 0; j < classes[i].numWaitlisted(); j++) {
                    classes[i].retrieveWaitlistedStudent(j, id, pri);
                    if (id == netid) {
                        M = 0;
                        break;
                    }
                    pos2++;
                }
                if (M == 0) { // if found on waitlist
                    // removes from waitlist and changes the priority to the new one
                    classes[i].removeWaitlistedStudent(pos2);
                    classes[i].waitlistStudent(netid, priority);
                    cout << "Student '" << netid << "' waitlisted for " << name << endl;
                } else {
                    classes[i].waitlistStudent(netid, priority);
                    cout << "Student '" << netid << "' waitlisted for " << name << endl;
                }
            } else {
                cout << "Student '" << netid << "' enrolled in " << name << endl;
            }
        }
    } // end of loop
    
    if (S == -1) { // class name invalid
        cout << "**Invalid class name, try again..." << endl;
    }
}

// 
// process:
// processes commands from the
// keyboard or from an input file
//

void processCommands(istream& input, bool promptUser, ClassReg classes[]) {
    string cmd, filename, name, netid, inf;
    int capacity, priority;
    ifstream infile;
    
    if (promptUser) { // if the user is inputting commands
        cout << endl << "Enter a command (help for more info, quit to stop)>" << endl;
    } 
    input >> cmd;
    
    // start cmd loop
    while ((cmd != "q") && (cmd != "quit")) {
        // help branch:
        // displays all available commands (minus help)
        if ((cmd == "h") || (cmd == "help")) {
            help();
        // stats branch:
        // lists number of enrolled and waitlisted
        // students for each class
        } else if ((cmd == "s") || (cmd == "stats")) {
            stats(classes);
        // list branch:
        // lists info about a specific class
        } else if ((cmd == "l") || (cmd == "list")) {
            input >> name;
            listClass(name, classes);
        // increase branch:
        // increases a class' capacity
        } else if ((cmd == "i") || (cmd == "increase")) {
            input >> name;
            input >> capacity;
            increaseCap(name, capacity, classes);
        // enroll branch:
        // enrolls students
        } else if ((cmd == "e") || (cmd == "enroll")) {
            input >> name;
            input >> netid;
            enroll(name, netid, classes);
        // waitlist branch:
        // waitlists students
        } else if ((cmd == "w") || (cmd == "waitlist")) {
            input >> name;
            input >> netid;
            input >> priority;
            waitlist(name, netid, priority, classes);
        // output branch:
        // outputs current enrollment data to a file
        } else if ((cmd == "o") || (cmd == "output")) {
            input >> inf;
            output(inf, classes);
        // process branch:
        // processes commands from a given command file
        } else if ((cmd == "process") || (cmd == "p")) {
            // if input is being taken from a file
            input >> filename;
            // check if file is good
            infile.open(filename);
            if (!infile.good()) { //file can't be opened/doesn't exist
                cout << "**Unable to open command file '" << filename << "'" << endl;
            } else { // file opened successfully
                cout << "**Processing commands from '" << filename << "'" << endl;
                processCommands(infile, false, classes); // taking in input from the given file
                cout << "**Done processing '" << filename << "'" << endl;
                infile.close();
            }
            
        } else {
            cout << "**Invalid command, please try again..." << endl;
        }
        if (promptUser) {
            cout << endl << "Enter a command (help for more info, quit to stop)>" << endl;
        } 
        input >> cmd;
    } // end of cmd loop
    
}


int main() {
    // making the class object and declaring name and cap vars
    ClassReg cs111, cs141, cs151, cs211, cs251; // creating class objects
    ClassReg classes[5] {cs111, cs141, cs151, cs211, cs251}; // creating an array of said objects

    ifstream infile;
    string name, netid, inf, cmd;
    int capacity, priority;
    
    // welcome message and filename prompt
    cout << "**CS Enrollment System**" << endl << "Enter enrollments filename>" << endl;
    cin >> inf;

    // making sure file is good, ends the program if it isn't
    infile.open(inf);
    if (!infile.good())
      {
         cout << endl << "**Error: unable to open enrollments file '" << inf << "'" << endl;
         return 0;
      }
    
    for (int i = 0; i < 5; i++) {
        // getting and setting class name and capacity
        infile >> name;
        classes[i].setName(name);
        infile >> capacity;
        classes[i].setCapacity(capacity);
        
        // enrolling students
        infile >> netid;
        while (netid != "#") {
            classes[i].enrollStudent(netid);
            infile >> netid;
        }
        
        // waitlisting students
        infile >> netid;
        while (netid != "#") {
            infile >> priority;
            classes[i].waitlistStudent(netid, priority);
            infile >> netid;
        }
    }
    infile.close();
    
    // processing commands
    processCommands(cin, true, classes);
    
    // all done
    cout << "**Done**" << endl;
    
    return 0;

}
