#include <vector>
#include <string>
#include <iostream>

using namespace std;

// Set a global variable for where the next empty spot in the tree is
long nextEmptyIndex = 0;

// Print the vector of vectors in vector form
void printVector(vector<vector<string>> tree){

    for(int i = 0; i < 7; i++){
        cout << '|';
        for(int j = 0; j < tree.size(); j++){
            cout << tree[j][i];
            cout << '|';
        }
        cout << endl;
    }
    cout << endl;
}

// Hash function that makes the entry 8 characters long
string hashFunction(string entry, string parentID, string ID, string lHash, string rHash){
    string null = "00000000";

    // Adds random char to make the entry 8 characters
    if(entry.length() < 8){
        for(int i = entry.length(); i < 8; i++) {
            entry.insert(0, 1, static_cast<char>(rand() % 95 + 32));
        }
    }

    // Sums every 8th character and then converts that sum to a character
    vector<long>entrySumVector (8, 0);
    for(short i = 0; i < entry.length(); i++){
        entrySumVector[i % 8] = entrySumVector[i % 8] + ((long)(entry.at(i))) * i;
    }
    string tempString;
    for(int i = 0; i < entrySumVector.size(); i++){
        tempString.push_back(static_cast<char>((entrySumVector[i] % 95) + 32));
    }

    vector<string>temp;

    // Pushback elements that are always present
    temp.push_back(tempString);
    temp.push_back(parentID);

    // Pushback if element is persent
    if(ID != null){
        temp.push_back(ID);
    }
    if(lHash != null){
        temp.push_back(lHash);
    }
    if(rHash != null){
        temp.push_back(rHash);
    }

    // Hash the strings
    string hashValue;
    for(int i = 0; i < 8; i++){
        long charSum = 0;
        for(int j = 0; j < temp.size(); j++){
            charSum = charSum + ((long)(temp[j].at(i))) * (6^(i*j));
        }
        hashValue.insert(0, 1, static_cast<char>(rand() % 95 + 32));
    }

    // Return hash
    return hashValue;
}

// Recursive function that updates all the parents in the tree
vector<vector<string>> updateParent(vector<vector<string>> tree, long parentIndex){
    string null = "00000000";

    // Decide if the the node is left or right
    bool left;
    if((parentIndex-1) % 2 == 0){
        left = true;
    }
    else{
        left = false;
    }

    // Update the left hash and history
    if(left){
        // Update left hash
        tree[(parentIndex - 1)/2][3] = hashFunction(tree[nextEmptyIndex][2], tree[nextEmptyIndex][1], tree[nextEmptyIndex][0], tree[nextEmptyIndex][3], tree[nextEmptyIndex][4]);

        // If history isn't null then append hash to history else set history equal hash
        if(tree[(parentIndex - 1)/2][5] == null){
            tree[(parentIndex - 1)/2][5] = tree[(parentIndex - 1)/2][3];
        }
        else{
            tree[(parentIndex - 1)/2][5].append(tree[(parentIndex - 1)/2][3]);
        }
    }
    // Update the right hash and history
    else{
        // Update the right hash
        tree[(parentIndex - 1)/2][4] = hashFunction(tree[nextEmptyIndex][2], tree[nextEmptyIndex][1], tree[nextEmptyIndex][0], tree[nextEmptyIndex][3], tree[nextEmptyIndex][4]);

        // If history isn't null then append hash to history else set history equal hash
        if(tree[(parentIndex - 1)/2][6] == null){
            tree[(parentIndex - 1)/2][6] = tree[(parentIndex - 1)/2][4];
        }
        else{
            tree[(parentIndex - 1)/2][6].append(tree[(parentIndex - 1)/2][4]);
        }
    }

    // If parent is root then return
    if((parentIndex - 1)/2 == 0) {
        return tree;
    }
    // else recursively call update parent with the parent index
    else{
        tree = updateParent(tree, (parentIndex-1)/2);

    }
    return tree;
}

// Create a new level of empty nodes
vector<vector<string>> createNewLevel(vector<vector<string>> tree, string null){

    long currentSize = tree.size();
    for(long i = 0; i < currentSize + 1; i++){
        vector<string> temp;
        temp.push_back(null);
        temp.push_back(tree[(nextEmptyIndex - 1) / 2][1]);
        temp.push_back(null);
        temp.push_back(null);
        temp.push_back(null);
        temp.push_back(null);
        temp.push_back(null);
        tree.push_back(temp);
    }
    return tree;
}

// Creates a random string of 8 characters
string randNum(){
    string randNum;
    for(int i = 0; i < 8; i++){
        randNum.append(to_string(rand() % 10));
    }
    return randNum;
}

// Update the next node with the new entry
vector<vector<string>> addEntry(vector<vector<string>> tree, string entry){

    string null = "00000000";

    // If creating roor then run this statement
    if(tree.empty()){
        vector<string>temp;
        string parentID = randNum();
        temp.push_back(hashFunction(entry, parentID, null, null, null));
        temp.push_back(parentID);
        temp.push_back(entry);
        temp.push_back(null);
        temp.push_back(null);
        temp.push_back(null);
        temp.push_back(null);
        tree.push_back(temp);
        nextEmptyIndex++;
    }
    // If the tree is full create a new row then add new information and update the tree
    else if(nextEmptyIndex == tree.size()){
        tree = createNewLevel(tree, null);
        vector<string>temp;
        temp.push_back(hashFunction(entry, tree[(nextEmptyIndex-1)/2][1], null, null, null));
        temp.push_back(tree[(nextEmptyIndex - 1)/2][0]);
        temp.push_back(entry);
        temp.push_back(null);
        temp.push_back(null);
        temp.push_back(null);
        temp.push_back(null);
        tree[nextEmptyIndex] = temp;
        tree = updateParent(tree, nextEmptyIndex);
        nextEmptyIndex++;
    }
    // Add new information then update the tree
    else{
        vector<string>temp;
        temp.push_back(hashFunction(entry, tree[(nextEmptyIndex-1)/2][1], null, null, null));
        temp.push_back(tree[(nextEmptyIndex - 1)/2][0]);
        temp.push_back(entry);
        temp.push_back(null);
        temp.push_back(null);
        temp.push_back(null);
        temp.push_back(null);
        tree[nextEmptyIndex] = temp;
        tree = updateParent(tree, nextEmptyIndex);
        nextEmptyIndex++;
    }

    return tree;
}
