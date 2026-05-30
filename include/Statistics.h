#pragma once
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cmath>

struct InsertResult {
    int steps;
    int rotations;
    int promotions;
};

struct StatsResult {
    int min_val;
    int max_val;
    double mean_val;
    double std_dev_val;
    double median_val;
};

class Statistics {
public:

    static StatsResult calculate_stats(std::vector<int> arr);

    static void print_tree_stats(
        std::string tree_name,
        std::vector<int> steps_arr,
        std::vector<int> rotations_arr,
        int tree_height,
        int leaf_count
    );

    static void print_skip_list_stats(
        std::string list_name,
        std::vector<int> steps_arr,
        std::vector<int> promotions_arr,
        int level_count
    );
};
