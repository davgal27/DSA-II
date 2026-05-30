#include <iostream>
#include <vector>
#include <cstdlib>
#include "KnuthShuffle.h"
#include "AVL_Tree.h"
#include "RB_Tree.h"
#include "SkipList.h"
#include "Statistics.h"

int main() {

    srand(1);

    std::vector<int> first_arr(10000);
    std::vector<int> second_arr(2000);


    // Create an array of 10k integers. vals start at 1 end at 10,000

    //at index 0, index val must = 1 
    //at index 9999, index val must = 10000
    // index val must = index + 1 

    for (int idx = 0; idx < 10000; idx++) {
        int idx_val = idx + 1;
        first_arr[idx] = idx_val;
    }

    Knuth_Shuffle(first_arr);

    //quick test to verify that numbers are shuffled 
    for (int idx = 0; idx < 100; idx++) {
        std::cout<< idx + 1 << ". " << first_arr[idx] << "\n";
    }

    AVLTree avl_tree;
    RedBlackTree rb_tree;
    SkipList skip_list;

    // insert all 10k integers from first_arr into AVL tree, Red-Black tree and Skip List

    for (int idx = 0; idx < 10000; idx++) {
        int idx_val = first_arr[idx];

        avl_tree.insert(idx_val);
        rb_tree.insert(idx_val);
        skip_list.insert(idx_val);
    }

    // create second array 

    for (int idx = 0; idx < 2000; idx++) {
        int idx_val = rand() % 20001;
        second_arr[idx] = idx_val;
    }

    //quick test to verify that the second array has random nmbers 
    for (int idx = 0; idx < 100; idx++) {
        std::cout << idx + 1 << ". " << second_arr[idx] << "\n";
    }

 
    // arrays to store AVL statistics
    std::vector<int> avl_steps(2000);
    std::vector<int> avl_rotations(2000);

    // arrays to store RB Tree statistics
    std::vector<int> rb_steps(2000);
    std::vector<int> rb_rotations(2000);

    // arrays to store Skip List statistics
    std::vector<int> skip_steps(2000);
    std::vector<int> skip_promotions(2000);

    // insert all values from second_arr into AVL tree
    // store steps and rotations for each insertion
    for (int idx = 0; idx < 2000; idx++) {
        int idx_val = second_arr[idx];

        InsertResult result = avl_tree.insert(idx_val);

        avl_steps[idx] = result.steps;
        avl_rotations[idx] = result.rotations;
    }

    // insert all values from second_arr into RB tree
    // store steps and rotations for each insertion
    for (int idx = 0; idx < 2000; idx++) {
        int idx_val = second_arr[idx];

        InsertResult result = rb_tree.insert(idx_val);

        rb_steps[idx] = result.steps;
        rb_rotations[idx] = result.rotations;
    }

    // insert all values from second_arr into Skip List
    // store steps and promotions for each insertion
    for (int idx = 0; idx < 2000; idx++) {
        int idx_val = second_arr[idx];

        InsertResult result = skip_list.insert(idx_val);

        skip_steps[idx] = result.steps;
        skip_promotions[idx] = result.promotions;
    }

    // print AVL statistics
    Statistics::print_tree_stats(
        "AVL Tree",
        avl_steps,
        avl_rotations,
        avl_tree.get_tree_height(),
        avl_tree.get_leaves()
    );

    // print RB statistics
    Statistics::print_tree_stats(
        "Red-Black Tree",
        rb_steps,
        rb_rotations,
        rb_tree.get_tree_height(),
        rb_tree.get_leaves()
    );

    // print Skip List statistics
    Statistics::print_skip_list_stats(
        "Skip List",
        skip_steps,
        skip_promotions,
        skip_list.get_levels()
    );

    return 0;
}