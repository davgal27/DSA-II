#include "Statistics.h"

// this file will handle both calculating and printing statistics

StatsResult Statistics::calculate_stats(std::vector<int> arr) {

    StatsResult stats;

    // if array is empty, all stats are 0 to prevent access to arr[1] when arr[1] doesnt exist

    if (arr.size() == 0) {
        stats.min_val = 0;
        stats.max_val = 0;
        stats.mean_val = 0;
        stats.std_dev_val = 0;
        stats.median_val = 0;

        return stats;
    }

    // sort array so min, max and median can be found
    std::sort(arr.begin(), arr.end());

    stats.min_val = arr[0]; // first value is least value 
    stats.max_val = arr[arr.size() - 1]; 

    // calculate mean
    double total = 0;

    for (int idx = 0; idx < arr.size(); idx++) {
        total = total + arr[idx];
    }

    stats.mean_val = total / arr.size();

    // calculate standard deviation
    double variance_total = 0;

    for (int idx = 0; idx < arr.size(); idx++) {
        double difference = arr[idx] - stats.mean_val;
        variance_total = variance_total + (difference * difference);
    }

    stats.std_dev_val = sqrt(variance_total / arr.size());

    // calculate median
    int middle_idx = arr.size() / 2;

    if (arr.size() % 2 == 0) {
        stats.median_val = (arr[middle_idx - 1] + arr[middle_idx]) / 2.0;
    }
    else {
        stats.median_val = arr[middle_idx];
    }

    return stats;
}


// Printing tree statistics 
void Statistics::print_tree_stats(
    std::string tree_name,
    std::vector<int> steps_arr,
    std::vector<int> rotations_arr,
    int tree_height,
    int leaf_count
) {

    StatsResult steps_stats = calculate_stats(steps_arr);
    StatsResult rotations_stats = calculate_stats(rotations_arr);

    std::cout << "\n====================================\n";
    std::cout << tree_name << " Statistics\n";
    std::cout << "====================================\n";

    // STEP STATISTICS
    std::cout << "\nSteps required to reach insertion point:\n";
    std::cout << "Minimum: " << steps_stats.min_val << "\n";
    std::cout << "Maximum: " << steps_stats.max_val << "\n";
    std::cout << "Mean: " << steps_stats.mean_val << "\n";
    std::cout << "Standard deviation: " << steps_stats.std_dev_val << "\n";
    std::cout << "Median: " << steps_stats.median_val << "\n";

    // ROTATION STATISTICS 
    std::cout << "\nRotations performed:\n";
    std::cout << "Minimum: " << rotations_stats.min_val << "\n";
    std::cout << "Maximum: " << rotations_stats.max_val << "\n";
    std::cout << "Mean: " << rotations_stats.mean_val << "\n";
    std::cout << "Standard deviation: " << rotations_stats.std_dev_val << "\n";
    std::cout << "Median: " << rotations_stats.median_val << "\n";

    // TREE INFORMATION
    std::cout << "\nTree information:\n";
    std::cout << "Height: " << tree_height << "\n";
    std::cout << "Number of leaves: " << leaf_count << "\n";
}


//printing statistics for the skip list 
void Statistics::print_skip_list_stats(
    std::string list_name,
    std::vector<int> steps_arr,
    std::vector<int> promotions_arr,
    int level_count
) {

    StatsResult steps_stats = calculate_stats(steps_arr);
    StatsResult promotions_stats = calculate_stats(promotions_arr);

    std::cout << "\n==============================\n";
    std::cout << list_name << " Statistics\n";
    std::cout << "================================\n";

    // STEP STATISTICS
    std::cout << "\nSteps required to reach insertion point:\n";
    std::cout << "Minimum: " << steps_stats.min_val << "\n";
    std::cout << "Maximum: " << steps_stats.max_val << "\n";
    std::cout << "Mean: " << steps_stats.mean_val << "\n";
    std::cout << "Standard deviation: " << steps_stats.std_dev_val << "\n";
    std::cout << "Median: " << steps_stats.median_val << "\n";

    //PROMOTION STATISTICS
    std::cout << "\nPromotions performed:\n";
    std::cout << "Minimum: " << promotions_stats.min_val << "\n";
    std::cout << "Maximum: " << promotions_stats.max_val << "\n";
    std::cout << "Mean: " << promotions_stats.mean_val << "\n";
    std::cout << "Standard deviation: " << promotions_stats.std_dev_val << "\n";
    std::cout << "Median: " << promotions_stats.median_val << "\n";

    // SKIP LIST INFORMATION 
    std::cout << "\nSkip List information:\n";
    std::cout << "Number of levels: " << level_count << "\n";
}