//
// Created by Warren Goodson on 5/3/2019.
//

#include <cmath>
#include "HashTable.h"

HashTable::HashTable(int n, int w): numObjects(n), capacity(w) {
    hTable.resize((unsigned long)n * 2);
//    for(int i = 0; i < n * 2; i++){
//        TableNode * node = new TableNode();
//        hTable[i] = node;
//    }
}

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
            // If current node's value is equal to the one we're adding, nothing to do
            if(current->value == value)
                return;
            current = current->next;
        }
        TableNode * newNode = new TableNode();
        newNode->value = value;
        newNode->i = i;
        newNode->j = j;
        current->next = newNode;
    }

}

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
    }
}

int HashTable::hashHelper(int i, int j) {
    int numBitsN = std::ceil(std::log2(numObjects));
    int numBitsW = std::ceil(std::log2(capacity));
    return 0;
}

HashTable::~HashTable() {
    for(auto &entry : hTable){
        delete(entry);
    }
}

