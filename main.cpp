#include <iostream>
#include <vector>
#include "Helper.cpp"

using namespace std;

int main() {

    vector<vector<string>> tree;

    string null = "00000000";

    string entry;

    while(true){

        do{
            cout << "Input: ";
            cin >> entry;
        }while(entry.size() > 1024);

        if(entry == "quit") {
            return 0;
        }

        if(entry == "print"){
//            printTree(tree);
        }
        if(entry == "printV"){
            printVector(tree);
        }

        else{
            tree = addEntry(tree, entry);
        }
    }
}