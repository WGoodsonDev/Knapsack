#ifndef KNAPSACK_HASHTABLE_H
#define KNAPSACK_HASHTABLE_H

#include <vector>
#include <string>
#include <algorithm>

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
    HashTable(int n, int w, int k);
    ~HashTable();
    void hashInsert(int i, int j, int value);
    int hashGet(int i, int j);

    int countCollisions();
    int getNumInsertions() const;
    int size(){ return hTable.size();}

private:
    int numObjects;
    int capacity;
    std::vector<TableNode*> hTable;

    int numInsertions;

    int hashHelper(int i, int j);

};


#endif //KNAPSACK_HASHTABLE_H
