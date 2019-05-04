//
// Created by Warren Goodson on 5/3/2019.
//

#include "HashTable.h"

HashTable::HashTable(int n, int w): numObjects(n), capacity(w) {
    hTable.resize((unsigned long)n * 2);
    for(int i = 0; i < n * 2; i++){
        TableNode node;
        hTable[i] = node;
    }
}

void HashTable::hashInsert(int i, int j, int value) {

}

int HashTable::hashGet(int i, int j) {

}

int HashTable::hashHelper(int i, int j) {
    return 0;
}

