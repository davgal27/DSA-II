#include <iostream>
#include <vector>
#include "KnuthShuffle.h"

int main() {
    // Create an array of 10k integers. vals start at 1 end at 10,000
    std::vector<int> arr(10000); // valid indexes from 0 - 9999

    //at index 0, index val must = 1 
    //at index 9999, index val must = 10000
    // index val must = index + 1 

    for (int idx = 0; idx < 10000; idx++) {
        int idx_val = idx + 1;
        arr[idx] = idx_val;
    }

    Knuth_Shuffle(arr);

    //quick test to verify that numbers are shuffled 
    for (int idx = 0; idx < 100; idx++) {
        std::cout<< idx + 1 << ". " << arr[idx] << "\n";
    }



    return 0;
}