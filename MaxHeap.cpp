#include "MaxHeap.h"

MaxHeap::MaxHeap(std::vector<std::pair<float, int>> input) {
    heap = input;
    heapBottomUp();
}

std::pair<float, int> MaxHeap::getMax() {
    return heap[1];
}

void MaxHeap::heapBottomUp() {
    float heapSize = (float)heap.size() - 1;
    for(int i = (int)std::floor(heapSize / 2.0f); i > 0; i--){
        int k = i;
        std::pair<float, int> v = heap[k];
        bool isHeap = false;
        while(!isHeap && 2 * k <= heapSize){
            int j = 2 * k;
            // There are 2 children
            if(j < heapSize){
                if(heap[j] < heap[j + 1])
                    j++;
            }
            if(v >= heap[j]){
                isHeap = true;
            }
            else{
                heap[k] = heap[j];
                k = j;
            }
        }
        heap[k] = v;
    }
}

void MaxHeap::deleteMax() {
    int heapSize = (int)heap.size();
    swap(1, heapSize - 1);
    heap.resize(static_cast<unsigned long>(heapSize - 1));
    heapBottomUp();
}

std::pair<float, int> MaxHeap::getDeleteMax() {
    std::pair<float, int> max = getMax();
    deleteMax();
    return max;
}

void MaxHeap::swap(int index1, int index2) {
    std::pair<float, int> temp = heap[index1];
    heap[index1] = heap[index2];
    heap[index2] = temp;
}
