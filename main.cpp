// By Warren Goodson and Erik Brownell

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>
#include <iomanip>
#include <map>
#include <algorithm>
#include "Knapsack.h"
#include "HashTable.h"
#include "MaxHeap.h"
#include "gnuplot.h"

void setInputFiles(char selection);
void traditionalKnapsack();
void spaceEfficientKnapsack();
int MFKnapsack(int i, int j, std::vector<int> &values, std::vector<int> &weights, HashTable *hTable);
void greedyBuiltInSort();
void greedyMaxHeap();
void compare();
void CreatePlot(std::string input_file,
                std::string output_file,
                int row1, int row2, int xtic, int ytic,
                int xr_min, int xr_max, int yr_min, int yr_max,
                std::string xlabel,
                std::string ylabel,
                std::string title);

std::string filenames[3];
int dataSetNum = -1;

int main(int argc, char* argv[]) {
    char choice = ' ';

    std::string fileChoice = "NONE";

    std::cout << "--------------------------------------------" << std::endl;
    std::cout << "Knapsack Solver\n\nby Warren Goodson and Erik Brownell\n";
    while(choice != 'q') {
        choice = '0';
        std::cout << "--------------------------------------------" << std::endl;
        std::cout << "Options:\n\n(s) Set Input Files (do this first)\n\n";
        std::cout << "(a) Traditional DP Approach\n(b) Space Efficient DP\n\n";
        std::cout << "(c) Greedy Approach (built-in sort)\n(d) Greedy Approach (max heap)\n\n(e) Comparison\n\n(q) Quit\n";
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
                spaceEfficientKnapsack();
                break;
            case 'c':
                greedyBuiltInSort();
                break;
            case 'd':
                greedyMaxHeap();
                break;
            case 'e':
                compare();
                break;
            case 'q':
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
    std::cout << "Space-efficient Dynamic Programming optimal value: " << optimalValue << std::endl << std::endl;

    std::cout << "n * W: " << n * capacity << std::endl;
    std::cout << "# of insertions: " << hTable.getNumInsertions() << std::endl;
    std::cout << "# of collisions: " << hTable.countCollisions() << std::endl;
    std::cout << "Size of table: " << hTable.size() << std::endl;

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
    int value;
    if(hTable->hashGet(i, j) < 0 && i > 0){
        if(j < weights[i]){
            value = MFKnapsack(i - 1, j, values, weights, hTable);
        }
        else{
            int a = MFKnapsack(i - 1, j, values, weights, hTable);
            int b = values[i] + MFKnapsack(i - 1, j - weights[i], values, weights, hTable);
            value = std::max(a, b);
        }
        hTable->hashInsert(i, j, value);
    }
    return hTable->hashGet(i, j);
}

void greedyBuiltInSort(){
    if (filenames[0].empty()){
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

    std::map<float, int, std::greater<float> > ratios;
    std::vector<int> results;
    results.resize(1);

    int n = (int)values.size() - 1; // Account for vector starting at index 1
    int capacity = kSack.getCapacity();

    // insert into ratios map
    for (int i = 1; i < n+1; i++){
        float f = (float)values[i] / weights[i];
        ratios.insert(std::pair<float, int>(f,i));
        std::cout << "Ratio: " << f << ", i: " << i << std::endl;
    }

    // calculate subset
    float tmp_cap = 0;
    int total_val = 0;
    for (auto& r: ratios){
        int i = r.second;
        if ((tmp_cap + weights[i]) < capacity){
            tmp_cap += weights[i];
            total_val += values[i];
            if(i > 0)
                results.push_back(i);
        }else
            break;
    }
    std::sort(results.begin(), results.end());

    // print
    std::cout << "Greedy Approach (built-in sort) Optimal value: " << total_val << std::endl;
    std::cout << "Greedy Approach (built-in sort) Optimal subset: {";
    for (int i = 0; i < results.size()-1; i++){
        std::cout << results[i] << ", ";
    }
    std::cout << results[results.size()-1] << "}" << std::endl;
    std::cout << "Greedy Approach (built-in sort) Time Taken: <INSERT_TIME>" << std::endl;
    std::cout << std::endl;
}

void greedyMaxHeap(){
    if (filenames[0].empty()){
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

    std::vector<std::pair<float, int>> ratios;
    std::vector<int> results;
    results.resize(1);

    int n = (int)values.size() - 1; // Account for vector starting at index 1
    int capacity = kSack.getCapacity();

    // insert into ratios vector
    ratios.emplace_back(std::pair<float, int>(-1.0f, -1));
    for (int i = 1; i <= n; i++){
        float f = (float)values[i] / weights[i];
        ratios.emplace_back(std::pair<float, int>(f,i));
    }

    // Build max heap from ratios
    MaxHeap mHeap = MaxHeap(ratios);
    for(int i = 0; i < n; i++){
        std::pair<float, int> current = mHeap.getDeleteMax();
        std::cout << "Ratio: " << current.first << ", i: " << current.second << std::endl;
    }


    // calculate subset
    float tmp_cap = 0;
    int total_val = 0;
    for (auto& r: ratios){
        int i = r.second;
        if ((tmp_cap + weights[i]) < capacity){
            tmp_cap += weights[i];
            total_val += values[i];
            if(i > 0)
                results.push_back(i);
        }else
            break;
    }
    std::sort(results.begin(), results.end());


    // print
    std::cout << "Greedy Approach (max heap) Optimal value: " << total_val << std::endl;
    std::cout << "Greedy Approach (max heap) Optimal subset: {";
    for (int i = 0; i < results.size()-1; i++){
        std::cout << results[i] << ", ";
    }
    std::cout << results[results.size()-1] << "}" << std::endl;
    std::cout << "Greedy Approach (max heap) Time Taken: <INSERT_TIME>" << std::endl;
    std::cout << std::endl;
}

void compare() {
    /** For this to work, it needs inputs to be in a file, currently I have a file
 *  called dummy_data.dat to test that it was working and it does.  Not sure how
 *  we want to do this but we need to run each function and put the output into a file
 *  so we can use it for the graphs.  I know someone on canvas asked if we
 *  need to create the graph in the program or not, at this time the instructor
 *  has not responded. I think it could be easier to simply to make the graphs ourselves,
 *  otherwise we may need to change the functions we have in main to pass by reference
 *  in order to grab the data we need. If you have a better idea let me know.
 */

    // collect data from all tests
    for (int i = 0; i < 9; i++){

    }

    // dummy data
    // Graph 1 for Task1 a/b
    std::string _title = "Test Title"; std::string _xlabel = "space"; std::string _ylabel = "time";
    int xt = 10, yt = 5;	// row/col increments
    int xr_min = 0, xr_max = 100, yr_min = 0, yr_max = 50;
    CreatePlot("dummy_data.dat", "TestGraph1.png", 1, 2, xt, yt, xr_min, xr_max, yr_min, yr_max, _xlabel, _ylabel, _title);

    // Graph 2 for Task2 a/b
    _title = "Test Title"; _xlabel = "number of inputs"; _ylabel = "time";
    xt = 10, yt = 5;
    xr_min = 0, xr_max = 100, yr_min = 0, yr_max = 50;
    CreatePlot("dummy_data.dat", "TestGraph2.png", 1, 2, xt, yt, xr_min, xr_max, yr_min, yr_max, _xlabel, _ylabel, _title);



    std::cout << "Created Graphs." << std::endl;
}

void CreatePlot(std::string input_file,
                std::string output_file,
                int row1, int row2, int xtic, int ytic,
                int xr_min, int xr_max, int yr_min, int yr_max, // range min, range max
                std::string xlabel,
                std::string ylabel,
                std::string title){

    gnuplot g;

    std::string xax = "set xtic " + std::to_string(xtic);
    std::string yax = "set ytic " + std::to_string(ytic);

    g("set term png");
    g("set output \"" + output_file + "\" ");
    g("set title \"" + title + "\" ");
    g("set grid");
    g("set pointsize");
    g("set xtic " + std::to_string(xtic));
    g("set ytic " + std::to_string(ytic));
    g("set xlabel '" + xlabel + "' ");
    g("set ylabel '" + ylabel + "' ");
    g("set xrange [" + std::to_string(xr_min) + ":" + std::to_string(xr_max) + "]");
    g("set yrange [" + std::to_string(yr_min) + ":" + std::to_string(yr_max) + "]");
    g("unset key");
    g("set timestamp");
    g("plot '" + input_file + "' using " + std::to_string(row1) + ":" + std::to_string(row2) + " lc rgb 'red'");
    g("quit");
}


