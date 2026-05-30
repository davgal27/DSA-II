#pragma once
#include "Statistics.h"
#include <iostream>

struct RBNode {
    int data;
    bool is_red;

    RBNode* left;
    RBNode* right;
    RBNode* parent;
};

class RedBlackTree {
private:
    RBNode* root;

    RBNode* create_node(int value);

    bool node_is_red(RBNode* node);

    void flip_colours(RBNode* node);
    void fix_red_red(RBNode* node, InsertResult& result);

    void rotate_left(RBNode* node);
    void rotate_right(RBNode* node);

    int get_node_height(RBNode* node);
    int count_leaves(RBNode* node);
    int get_max(int val_one, int val_two);

public:
    RedBlackTree();

    InsertResult insert(int value);

    int get_tree_height();
    int get_leaves();
};