#include "Knapsack.h"

Knapsack::Knapsack(std::string filenames[], int dataSetNum) {
    std::ifstream inStream;

    // Set all vectors to start at index 1 (for consistency)
    values.push_back(-1);
    weights.push_back(-1);

    // Set data set number
    dataSet = dataSetNum;

    // filenames:
    // [0]: values
    // [1]: weights
    // [2]: capacity

    int currentLine;
    // Get values
    std::cout << "Getting values..." << std::endl;
    inStream.open(filenames[0], std::ios::in);
    if(inStream.is_open()){
        while(!inStream.eof()){
            inStream >> currentLine;
            if(!inStream.fail()){
                // std::cout << currentLine << std::endl;
                values.push_back(currentLine);
            }
        }
    } else {
        std::cout << "ERROR: failed to open " << filenames[0] << std::endl;
        std::cout << "Exiting..." << std::endl;
        exit(1);
    }
    inStream.close();

    // Get weights
    std::cout << "Getting weights..." << std::endl;
    inStream.open(filenames[1], std::ios::in);
    if(inStream.is_open()){
        while(!inStream.eof()){
            inStream >> currentLine;
            if(!inStream.fail()){
                // std::cout << currentLine << std::endl;
                weights.push_back(currentLine);
            }

        }
    } else {
        std::cout << "ERROR: failed to open " << filenames[0] << std::endl;
        std::cout << "Exiting..." << std::endl;
        exit(2);
    }
    inStream.close();

    // Get capacity
    std::cout << "Getting capacity..." << std::endl;
    inStream.open(filenames[2], std::ios::in);
    if(inStream.is_open()){
        inStream >> capacity;
    } else {
        std::cout << "ERROR: failed to open " << filenames[0] << std::endl;
        std::cout << "Exiting..." << std::endl;
        exit(3);
    }
    inStream.close();

    std::cout << std::endl;

}

const std::vector<int> &Knapsack::getValues() const {
    return values;
}

const std::vector<int> &Knapsack::getWeights() const {
    return weights;
}

int Knapsack::getCapacity() const {
    return capacity;
}

int Knapsack::getDataSet() const {
    return dataSet;
}
