#include <cmath>
#include <sstream>
#include "HashTable.h"

HashTable::HashTable(int n, int w, int k): numObjects(n), capacity(w), numInsertions(0) {
    hTable.resize(k);
    // Need to initialize (i, 0) and (0, j) rows to all 0's
    for(int i = 0; i < n; i++)
        hashInsert(i, 0, 0);
    for(int j = 0; j < w + 1; j++)
        hashInsert(0, j, 0);

}

// Insert (i, j, value) into hash table
void HashTable::hashInsert(int i, int j, int value) {
    int index = hashHelper(i, j);
    TableNode *current = hTable[index];
    // If node at that index is nullptr, create new node with value and insert it
    if(!current){
        current = new TableNode();
        current->value = value;
        current->i = i;
        current->j = j;
        hTable[index] = current;
    }
    else{
        // Get to end of linked list and insert
        while(current->next){
            // If current node's (i, j) pair is equal to the one we're adding, nothing to do
            if(current->i == i && current->j == j)
                return;
            current = current->next;
        }
        TableNode * newNode = new TableNode();
        newNode->value = value;
        newNode->i = i;
        newNode->j = j;
        current->next = newNode;
    }
    numInsertions++;
}

// Get value from hash table. If entry at hashed value is empty, return -1
int HashTable::hashGet(int i, int j) {
    int index = hashHelper(i, j);
    TableNode *current = hTable[index];

    if(!current){
        return -1;
    }
    else{
        if(current->i == i && current->j == j)
            return current->value;
        while(current->next){
            if(current->i == i && current->j == j)
                return current->value;
            current = current->next;
        }
        if(current->i == i && current->j == j)
            return current->value;
        else{
            return -1;
        }
    }
}

// The actual hash function
int HashTable::hashHelper(int i, int j) {
    int numBitsN = (int)std::ceil(std::log2(numObjects));
    int numBitsW = (int)std::ceil(std::log2(capacity));

    std::string iBinary;
    std::string jBinary;
    int iTemp = i;
    int jTemp = j;
    int remainder = 0;

    // Construct binary representation
    while(iTemp > 0){
        remainder = iTemp%2;
        iTemp /= 2;

        if(remainder == 0){
            iBinary += "0";
        } else {
            iBinary += "1";
        }
    }
    // Pad with leading 0s
    while(iBinary.size() < numBitsN)
        iBinary += "0";

    // Construct binary representation
    while(jTemp > 0){
        remainder = jTemp%2;
        jTemp /= 2;

        if(remainder == 0){
            jBinary += "0";
        } else {
            jBinary += "1";
        }
    }
    // Pad with leading 0s
    while(jBinary.size() < numBitsW)
        jBinary += "0";

    std::reverse(iBinary.begin(), iBinary.end());
    std::reverse(jBinary.begin(), jBinary.end());

    std::string rIJ = "1" + iBinary + jBinary;
    int rIJInt = std::stoi(rIJ, nullptr, 2);

    return (int)(rIJInt % hTable.size());
}

HashTable::~HashTable() {
    for(auto &entry : hTable){
        delete(entry);
    }
}

int HashTable::countCollisions() {
    int colCount = 0;
    for(auto &node : hTable){
        auto current = node;
        if(current){
            while(current->next){
                colCount++;
                current = current->next;
            }
        }
    }
    return colCount;
}

int HashTable::getNumInsertions() const {
    return numInsertions;
}

