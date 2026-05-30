#pragma once
#include "Statistics.h"
#include <iostream>

struct AVLNode {
    int data;
    int height;

    AVLNode* left;
    AVLNode* right;
};

class AVLTree {
private:
    AVLNode* root;

    AVLNode* create_node(int value);

    int get_node_height(AVLNode* node);
    int get_balance_factor(AVLNode* node);
    int get_max(int val_one, int val_two);

    int count_leaves(AVLNode* node);

    AVLNode* insert_node(AVLNode* node, int value, InsertResult& result);

    AVLNode* rotate_left(AVLNode* node);
    AVLNode* rotate_right(AVLNode* node);

public:
    AVLTree();

    InsertResult insert(int value);

    int get_tree_height();
    int get_leaves();
};