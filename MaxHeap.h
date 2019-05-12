#include <vector>
#include <map>
#include <cmath>

#ifndef KNAPSACK_MAXHEAP_H
#define KNAPSACK_MAXHEAP_H


class MaxHeap {
public:
    MaxHeap(std::vector<std::pair<float, int>> input);

    std::pair<float, int> getMax();
    void deleteMax();
    std::pair<float, int> getDeleteMax();
    int size(){ return (int)heap.size();}

private:
    void heapBottomUp();
    void swap(int index1, int index2);

    std::vector<std::pair<float, int>> heap;
};


#endif //KNAPSACK_MAXHEAP_H
