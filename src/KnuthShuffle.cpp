#include "KnuthShuffle.h"
#include <random>

void Knuth_Shuffle(std::vector<int>& arr) {

    // position shuffle_line = current dividing line 
    // each iteration, position shuffle_line = -1
    // item toshuffle is random, swaps place with position i

    // Based on video explaining Knuth Shuffle by James Cutajar 
    
    int last_index = arr.size() - 1; //idx 9999 = size of 10000 - 1 
    int first_index = 0;

    for (int i = last_index; i > 0; i--) {
        int shuffle_line = i;
        int to_shuffle = rand() % (shuffle_line - first_index + 1) + first_index;
        std::swap(arr[shuffle_line], arr[to_shuffle]);
    }
}
