// By Warren Goodson and Erik Brownell

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include "Knapsack.h"
#include "HashTable.h"

void setInputFiles(char selection);
void traditionalKnapsack();
void spaceEfficientKnapsack();
int MFKnapsack(int i, int j, std::vector<int> &values, std::vector<int> &weights, HashTable *hTable);
void greedyBuiltInSort();
void greedyMaxHeap();
void compare();

std::string filenames[3];
int dataSetNum = -1;

int main(int argc, char* argv[]) {
    char choice = ' ';

    std::string fileChoice = "NONE";

    std::cout << "Knapsack Solver\nby Warren Goodson and Erik Brownell\n\n";
    while(choice != 'q') {
        choice = '0';
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "Options: (s) Set Input Files (do this first), (a) Traditional DP Approach, (b) Space Efficient DP,\n\t(c) Greedy Approach (built-in sort), (d) Greedy Approach (max heap), (e) Comparison, (q) Quit\n";
        std::cin >> choice;

        char dataSelection = ' ';

        switch (choice) {
            case 's':
                std::cout << "Enter a number between 0 and 8 (inclusive) to select data set:" << std::endl;
                std::cin >> dataSelection;
                while(dataSelection < 48 || dataSelection > 56){
                    std::cout << "Error: please enter a number between 0 and 8, inclusive" << std::endl;
                    std::cin >> dataSelection;
                }
                setInputFiles(dataSelection);
                std::cout << "Data set 0" << dataSelection << " selected successfully." << std::endl;
                break;
            case 'a':
                traditionalKnapsack();
                break;
            case 'b':

                break;
            case 'c':

                break;
            default:
                std::cout << "Please choose either (a), (b), (c), (d), (e), or (s)\n";
        }
    }
    return 0;
}

void setInputFiles(char selection){

    char* dSet = &selection;
    dataSetNum = strtol(dSet, nullptr, 10);

    std::stringstream vName;
    vName << "./test_data/p0" << selection << "_v.txt";

    std::stringstream wName;
    wName << "./test_data/p0" << selection << "_w.txt";

    std::stringstream cName;
    cName << "./test_data/p0" << selection << "_c.txt";

    filenames[0] = vName.str();
    filenames[1] = wName.str();
    filenames[2] = cName.str();

}

void traditionalKnapsack(){
    if(filenames[0].empty()){
        std::cout << "Please select a data set (s)" << std::endl;
        return;
    }


    Knapsack kSack = Knapsack(filenames, dataSetNum);

    std::cout << "Testing Knapsack data structure..." << std::endl;
    std::cout << "Data set: 0" << kSack.getDataSet() << std::endl;
    std::cout << "Total number of items: " << kSack.getValues().size() - 1 << std::endl;
    std::cout << "Capacity of Knapsack: " << kSack.getCapacity() << std::endl;
    std::cout << std::endl;

    std::cout << "Computing optimal value for knapsack..." << std::endl;
    std::cout << std::endl;
    std::vector<int> values = kSack.getValues();
    std::vector<int> weights = kSack.getWeights();

    int n = (int)values.size() - 1; // Account for vector starting at index 1
    int capacity = kSack.getCapacity();


    int F[n+1][capacity+1];
    // Zero out top row and leftmost column
    for(int i = 0; i <= n; i++)
        F[i][0] = 0;
    for(int j = 0; j <= capacity; j++)
        F[0][j] = 0;

    // Populate the table
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= capacity; j++){
            if(j - weights[i] < 0){
                // Not picked
                F[i][j] = F[i-1][j];
            } else {
                // Picked
                F[i][j] = std::max(F[i-1][j], values[i] + F[i-1][j-weights[i]]);
            }
        }
    }

    std::cout << "Traditional Dynamic Programming optimal value: " << F[n][capacity] << std::endl;

    // Backtrack to find the optimal subset
    std::vector<int> optimalSubset;

    int i = n;
    int j = capacity;
    while(i >= 0 && j > 0){
        if((j - weights[i] >= 0) && (values[i] + F[i-1][j-weights[i]] > F[i-1][j])){
            optimalSubset.push_back(i);
            j -= weights[i];
            i--;
        } else {
            i--;
        }
    }

    std::cout << "Traditional Dynamic Programming optimal subset: {";
    for(int a = (int)optimalSubset.size() - 1; a > 0 ; a--){
        std::cout << optimalSubset[a] << ", ";
    }
    std::cout << optimalSubset[0] << "}" << std::endl;


}

void spaceEfficientKnapsack() {
    if(filenames[0].empty()){
        std::cout << "Please select a data set (s)" << std::endl;
        return;
    }

    Knapsack kSack = Knapsack(filenames, dataSetNum);

    std::cout << "Testing Knapsack data structure..." << std::endl;
    std::cout << "Data set: 0" << kSack.getDataSet() << std::endl;
    std::cout << "Total number of items: " << kSack.getValues().size() - 1 << std::endl;
    std::cout << "Capacity of Knapsack: " << kSack.getCapacity() << std::endl;
    std::cout << std::endl;

    std::cout << "Computing optimal value for knapsack..." << std::endl;
    std::cout << std::endl;
    std::vector<int> values = kSack.getValues();
    std::vector<int> weights = kSack.getWeights();

    int n = (int)values.size() - 1; // Account for vector starting at index 1
    int capacity = kSack.getCapacity();

    HashTable hTable = HashTable(n, capacity);

    // Use MFKnapsack to get optimal value of subset

    int optimalValue = MFKnapsack(n, capacity, values, weights, &hTable);
    std::cout << "Space-efficient Dynamic Programming optimal value: " << optimalValue << std::endl;

    // Backtrack to find the optimal subset
    std::vector<int> optimalSubset;

    int i = n;
    int j = capacity;
    while(i >= 0 && j > 0){
        if((j - weights[i] >= 0) && (values[i] + hTable.hashGet(i-1, j-weights[i]) > hTable.hashGet(i-1, j))){
            optimalSubset.push_back(i);
            j -= weights[i];
            i--;
        } else {
            i--;
        }
    }

    std::cout << "Space-efficient Dynamic Programming optimal subset: {";
    for(int a = (int)optimalSubset.size() - 1; a > 0 ; a--){
        std::cout << optimalSubset[a] << ", ";
    }
    std::cout << optimalSubset[0] << "}" << std::endl;

}

int MFKnapsack(int i, int j, std::vector<int> &values, std::vector<int> &weights, HashTable *hTable) {
    if(hTable->hashGet(i, j) < 0){
        int value;
        if(j < weights[i]){
            value = MFKnapsack(i - 1, j, values, weights, hTable);
        }
        else{
            value = std::max(MFKnapsack(i - 1, j, values, weights, hTable), values[i] + MFKnapsack(i - 1, j - weights[i], values, weights, hTable));
        }
        hTable->hashInsert(i, j, value);
    }
    return hTable->hashGet(i, j);
}

void greedyBuiltInSort(){

}

void greedyMaxHeap(){

}

void compare() {


}


