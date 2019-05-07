//
// Created by Warren Goodson on 5/3/2019.
//

#ifndef KNAPSACK_HASHTABLE_H
#define KNAPSACK_HASHTABLE_H

#include <vector>
#include <string>

// template <typename  T>
struct TableNode{
    TableNode(){
        value = -1;
        i = -1;
        j = -1;
        next = nullptr;
    }
    int value;
    int i;
    int j;
    TableNode * next;
};

class HashTable {

public:
    HashTable(int n, int w);
    ~HashTable();
    void hashInsert(int i, int j, int value);
    int hashGet(int i, int j);


private:
    int numObjects;
    int capacity;
    std::vector<TableNode*> hTable;

    int hashHelper(int i, int j);

};


#endif //KNAPSACK_HASHTABLE_H
