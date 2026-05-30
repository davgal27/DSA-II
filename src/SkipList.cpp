#include "SkipList.h"
#include <iostream>
#include <cstdlib>
#include <climits> 

// start with empty head node
// INT_MIN is used as the -infinity start value
SkipList::SkipList() {

    max_level = 32; // as implemented in the skip list cookbook by William Pugh 
    highest_current_level = 1;

    start_node = create_node(INT_MIN, max_level);
}

// create new node
// node_level decides how many forward pointers the node has
SkipNode* SkipList::create_node(int value, int node_level) {

    SkipNode* new_node = new SkipNode;

    new_node->data = value;
    new_node->forward.resize(node_level);

    for (int idx = 0; idx < node_level; idx++) {
        new_node->forward[idx] = nullptr;
    }

    return new_node;
}

// flip a coin
// Heads means promote
// Tails means stop promoting
int SkipList::flip_coin() {

    if (rand() % 2 == 0) {
        return Heads;
    }
    else {
        return Tails;
    }
}

// generate level for the new node
// level 1 means bottom list only
// each Heads promotes the node one level higher
int SkipList::generate_level(InsertResult& result) {

    int generated_level = 1;

    while (flip_coin() == Heads && generated_level < max_level) {
        generated_level++;
        result.promotions++;
    }

    return generated_level;
}

// searches for the position to insert the value
// update[level] stores the node before the insertion point at each level
// structure / pseudo code from skiplist cookbook 
SkipNode* SkipList::search_insert(
    int value,
    std::vector<SkipNode*>& update,
    InsertResult& result
) {

    SkipNode* current_node = start_node;

    // start from highest current level
    // move right while the next value is less than or equal to value
    // equal values go right so duplicates can be inserted
    for (int level = highest_current_level - 1; level >= 0; level--) {

        while (
            current_node->forward[level] != nullptr &&
            current_node->forward[level]->data <= value
        ) {
            current_node = current_node->forward[level];

            // each forward movement counts as one step

            result.steps++;
        }

        // store node before insertion point at this level

        update[level] = current_node;
    }

    return current_node;
}

// creates the new node and updates the forward pointers
void SkipList::create_and_insert(
    int value,
    int node_level,
    std::vector<SkipNode*>& update
) {

    SkipNode* new_node = create_node(value, node_level);

    for (int level = 0; level < node_level; level++) {

        new_node->forward[level] = update[level]->forward[level];
        update[level]->forward[level] = new_node;
    }
}

// main insert function
// searches for position, generates level, then inserts node
InsertResult SkipList::insert(int value) {

    InsertResult result;

    result.steps = 0;
    result.rotations = 0;
    result.promotions = 0;

    std::vector<SkipNode*> update(max_level);

    // search for insertion position
    search_insert(value, update, result);

    // randomly generate node level using coin flips
    int generated_level = generate_level(result);

    // if new node has more levels than current skip list,
    // start_node becomes the previous node for those new levels
    // adapted from pseudocode from skiplist cookbook
    if (generated_level > highest_current_level) {

        for (int level = highest_current_level; level < generated_level; level++) {
            update[level] = start_node;
        }

        highest_current_level = generated_level;
    }

    // insert the node into each required level
    create_and_insert(value, generated_level, update);

    return result;
}

// return number of levels currently used in the skip list
int SkipList::get_levels() {
    return highest_current_level;
}