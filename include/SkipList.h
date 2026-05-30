#pragma once

#include "Statistics.h"
#include <iostream>
#include <cstdlib>
#include <climits>
#include <vector>

struct SkipNode {
    int data;
    std::vector<SkipNode*> forward;
};

class SkipList {
private:
    SkipNode* start_node;

    int max_level;
    int highest_current_level;

    enum {
        Heads,
        Tails
    };

    SkipNode* create_node(int value, int node_level);

    int flip_coin();

    int generate_level(InsertResult& result);

    SkipNode* search_insert(
        int value,
        std::vector<SkipNode*>& update,
        InsertResult& result
    );

    void create_and_insert(
        int value,
        int node_level,
        std::vector<SkipNode*>& update
    );

public:
    SkipList();

    InsertResult insert(int value);

    int get_levels();
};