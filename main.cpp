// By Warren Goodson and Erik Brownell

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include "Knapsack.h"

int setInputFiles(char selection);
void traditionalKnapsack();
void spaceEfficientKnapsack();
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
                if(setInputFiles(dataSelection) == 0)
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

int setInputFiles(char selection){
    if(selection < 48 || selection > 56){
        std::cout << "Error: please enter a number between 0 and 8, inclusive" << std::endl;
        return -1;
    }

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


    return 0;
}

void traditionalKnapsack(){
    if(filenames[0].empty()){
        std::cout << "Please select a data set (s)" << std::endl;
        return;
    }


    Knapsack sack = Knapsack(filenames, dataSetNum);

    std::cout << "Testing Knapsack data structure..." << std::endl;
    std::cout << "Data set: 0" << sack.getDataSet() << std::endl;
    std::cout << "Number of entries in values vector: " << sack.getValues().size() << std::endl;
    std::cout << "Number of entries in weights vector: " << sack.getWeights().size() << std::endl;
    std::cout << "Capacity of Knapsack: " << sack.getCapacity() << std::endl;
}

void spaceEfficientKnapsack() {
    int choice;


    while(true){
        choice = 0;
        std::cout <<"Options: (1) display index, (2) search, (3) save index, (4) quit\n";
        std::cin >> choice;

        //Quit
        if(choice < 1 || choice > 3)
            break;
        switch(choice){
            case 1:

                break;
            case 2:

                break;
            case 3:

                break;
        }
    }
}

void greedyBuiltInSort(){

}

void greedyMaxHeap(){

}

void compare() {


}
