#ifndef KNAPSACK_KNAPSACK_H
#define KNAPSACK_KNAPSACK_H

#include <iostream>
#include <fstream>
#include <vector>

class Knapsack {
public:
    Knapsack(std::string filenames[], int dataSetNum);

    const std::vector<int> &getValues() const;
    const std::vector<int> &getWeights() const;
    int getCapacity() const;
    int getDataSet() const;

private:
    int dataSet;
    std::vector<int> values;
    std::vector<int> weights;
    int capacity;
};


#endif //KNAPSACK_KNAPSACK_H
