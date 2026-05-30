#include "AVL_Tree.h"
// start tree as null 
AVLTree::AVLTree() {
    root = nullptr;
}

// create new node 
AVLNode* AVLTree::create_node(int value) {

    AVLNode* new_node = new AVLNode;

    new_node->data = value;
    new_node->height = 1;
    new_node->left = nullptr;
    new_node->right = nullptr;

    return new_node;
}

// get height of specific node 
int AVLTree::get_node_height(AVLNode* node) {

    if (node == nullptr) {
        return 0;
    }

    return node->height;
}

// find max tree hight with root 
int AVLTree::get_tree_height() {
    return get_node_height(root);
}

// count leaves
int AVLTree::count_leaves(AVLNode* node) {

    if (node == nullptr) {
        return 0;
    }

    if (node->left == nullptr && node->right == nullptr) {
        return 1;
    }

    return count_leaves(node->left) + count_leaves(node->right);
}

// find total leaves by counting from root 
int AVLTree::get_leaves() {
    return count_leaves(root);
}

// maximum
int AVLTree::get_max(int val_one, int val_two) {

    if (val_one > val_two) {
        return val_one;
    }
    else {
        return val_two;
    }
}

// balance factor = left - right height 
int AVLTree::get_balance_factor(AVLNode* node) {

    if (node == nullptr) {
        return 0;
    }

    return get_node_height(node->left) - get_node_height(node->right);
}

// =========================================================================
// INSERTIONS
// =======================================================================
// first insert like a normal BST
// then update height, balance factor, and check if it is valid
// if balance factor is invalid, rotate

// insert function
InsertResult AVLTree::insert(int value) {

    InsertResult result;

    result.steps = 0;
    result.rotations = 0;
    result.promotions = 0;

    root = insert_node(root, value, result);

    return result;
}

AVLNode* AVLTree::insert_node(AVLNode* node, int value, InsertResult& result) {

    // if empty position is found, create the new node
    if (node == nullptr) {
        AVLNode* new_node = create_node(value);
        return new_node;
    }

    //node visited = step added 
    result.steps++;

    // Case 1: Value is smaller 
    if (value < node->data) {
        node->left = insert_node(node->left, value, result);
    }

    // Case 2: Value is equal or larger
    else {
        node->right = insert_node(node->right, value, result);
    }

    // update height after insertion
    int left_height = get_node_height(node->left);
    int right_height = get_node_height(node->right);
    node->height = 1 + get_max(left_height, right_height);

    // balance factor = height(left subtree) - height(right subtree)
    int balance_factor = get_balance_factor(node);

    // if balance factor is more than 1 or less than -1, AVL condition violated 
// ==============================================================================
    // LL CASE :value in left subtree of left child 

    if (balance_factor > 1 && value < node->left->data) {

        if (result.rotations == 0) {
            result.rotations++;
        }
        return rotate_right(node);
    }
// ===============================================================================
    // RR case: value in right subtree of right child 

    if (balance_factor < -1 && value >= node->right->data) {

        if (result.rotations == 0) {
            result.rotations++;
        }
        return rotate_left(node);
    }
// ==================================================================
    // LR case: value in right subtree of left child 

    if (balance_factor > 1 && value >= node->left->data) {

        if (result.rotations == 0) {
            result.rotations++;
        }
        node->left = rotate_left(node->left);
        return rotate_right(node);
    }
// ====================================================================
    // RL case: value in left subtree of right child 

    if (balance_factor < -1 && value < node->right->data) {

        if (result.rotations == 0) {
            result.rotations++;
        }
        node->right = rotate_right(node->right);
        return rotate_left(node);
    }
// ===========================================================
    // Case already balanced: return node ptr 

    return node;
}

// ==============================================================
// ROTATIONS
//===============================================================

// LEFT ROTATION 
AVLNode* AVLTree::rotate_left(AVLNode* node) {

    AVLNode* right_child = node->right; 
    AVLNode* middle_subtree = right_child->left;

    right_child->left = node;
    node->right = middle_subtree;

    // update heights after rotation
    int node_left_height = get_node_height(node->left);
    int node_right_height = get_node_height(node->right);

    node->height = 1 + get_max(node_left_height, node_right_height);

    int right_left_height = get_node_height(right_child->left);
    int right_right_height = get_node_height(right_child->right);

    right_child->height = 1 + get_max(right_left_height, right_right_height);

    return right_child;
}

// RIGHT ROTATION
AVLNode* AVLTree::rotate_right(AVLNode* node) {

    AVLNode* left_child = node->left;
    AVLNode* middle_subtree = left_child->right;

    left_child->right = node;
    node->left = middle_subtree;

    // update heights 
    int node_left_height = get_node_height(node->left);
    int node_right_height = get_node_height(node->right);

    node->height = 1 + get_max(node_left_height, node_right_height);

    int left_left_height = get_node_height(left_child->left);
    int left_right_height = get_node_height(left_child->right);

    left_child->height = 1 + get_max(left_left_height, left_right_height);

    return left_child;
}
