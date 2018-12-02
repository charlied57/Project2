#include <iostream>
#include <vector>
#include "Helper.cpp"

using namespace std;

int main() {

    vector<vector<string>> tree;

    string null = "00000000";
    string instructions = "Input string less than 1024 characters, print-tree, print-vector, help, quit.";

    string entry;

    cout << instructions << endl;

    // Loop inputs
    while(true){

        // Loop if more than 1024 characters
        do{
            cout << "Input: ";
            cin >> entry;
            cout << endl;
        }while(entry.size() > 1024);

        // Quit the program
        if(entry == "quit") {
            return 0;
        }

        // Print in tree form(not working currently)
        else if(entry == "print-tree"){
//            printTree(tree);
        }

        // Print in vector form(kinda messy)
        else if(entry == "print-vector"){
            printVector(tree);
        }

        // Print instructions
        else if(entry == "help"){
            cout << endl << instructions << endl << endl;
        }

        // Add next entry and begin the main program
        else{
            tree = addEntry(tree, entry);
        }
    }
}