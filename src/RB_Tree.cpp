#include "RB_Tree.h"

// start tree as null
RedBlackTree::RedBlackTree() {
    root = nullptr;
}

// creates a new Red-Black node
// new nodes are inserted as red first
RBNode* RedBlackTree::create_node(int value) {

    RBNode* new_node = new RBNode;

    new_node->data = value;
    new_node->is_red = true;

    new_node->left = nullptr;
    new_node->right = nullptr;
    new_node->parent = nullptr;

    return new_node;
}

// treat null nodes as black
bool RedBlackTree::node_is_red(RBNode* node) {

    if (node == nullptr) {
        return false;
    }

    return node->is_red;
}

// get height of specific node
int RedBlackTree::get_node_height(RBNode* node) {

    if (node == nullptr) {
        return 0;
    }

    int left_height = get_node_height(node->left);
    int right_height = get_node_height(node->right);

    return 1 + get_max(left_height, right_height);
}

// find max tree height with root
int RedBlackTree::get_tree_height() {
    return get_node_height(root);
}

// count leaves
int RedBlackTree::count_leaves(RBNode* node) {

    if (node == nullptr) {
        return 0;
    }

    if (node->left == nullptr && node->right == nullptr) {
        return 1;
    }

    return count_leaves(node->left) + count_leaves(node->right);
}

// find total leaves by counting from root
int RedBlackTree::get_leaves() {
    return count_leaves(root);
}

// maximum
int RedBlackTree::get_max(int val_one, int val_two) {

    if (val_one > val_two) {
        return val_one;
    }
    else {
        return val_two;
    }
}

// =========================================================================
// INSERTIONS
// =======================================================================
// Top down approach taken: fix as you go along 
InsertResult RedBlackTree::insert(int value) {

    InsertResult result;
    result.steps = 0;
    result.rotations = 0;
    result.promotions = 0;
    RBNode* parent_node = nullptr;
    RBNode* current_node = root;

    // If tree empty -> insert root as black 
    if (root == nullptr) {
        root = create_node(value);
        root->is_red = false;

        return result;
    }

    // search down tree like a normal BST
    // but on the way down, split nodes that have two red children
    while (current_node != nullptr) {

        // node visited = step added
        result.steps++;

        // top-down colour flip
        // current node two red children -> current node = red, both children = black 
        if (node_is_red(current_node->left) && node_is_red(current_node->right)) {

            flip_colours(current_node);

            // root must always stay black
            if (current_node == root) {
                current_node->is_red = false;
            }

            // if colour flip created red parent and red child,
            // fix it immediately before going further down
            else if (node_is_red(current_node->parent)) {
                fix_red_red(current_node, result);
            }
        }

        parent_node = current_node;

        // normal BST search: smaller values go left, equal or larger right
        if (value < current_node->data) {
            current_node = current_node->left;
        }else {
            current_node = current_node->right;
        }
    }

    // IF current_node is null, insertion point found
    RBNode* new_node = create_node(value);
    new_node->parent = parent_node;

    if (value < parent_node->data) {
        parent_node->left = new_node;
    }
    else {
        parent_node->right = new_node;
    }

    // new node is red
    // if parent is red, we have a red-red violation
    // this can be fixed with one single or double rotation

    if (node_is_red(parent_node)) {
        fix_red_red(new_node, result);
    }

    // root must always be black
    root->is_red = false;

    return result;
}

// flip colours for top-down insertion
// current node becomes red
// both red children become black
void RedBlackTree::flip_colours(RBNode* node) {

    node->is_red = true;

    if (node->left != nullptr) {
        node->left->is_red = false;
    }

    if (node->right != nullptr) {
        node->right->is_red = false;
    }
}

// fixes red-red violation: node and parent both red
void RedBlackTree::fix_red_red(RBNode* node, InsertResult& result) {

    RBNode* parent_node = node->parent;

    if (parent_node == nullptr) {
        return;
    }

    RBNode* grandparent_node = parent_node->parent;

    if (grandparent_node == nullptr) {
        parent_node->is_red = false;
        return;
    }

    // parent is left child of grandparent==========================
    if (parent_node == grandparent_node->left) {

        // LL CASE =============================
        // node is outside grandparent
        if (node == parent_node->left) {

            parent_node->is_red = false;
            grandparent_node->is_red = true;

            rotate_right(grandparent_node);

            result.rotations++;
        }

        // LR case =============================
        // node is inside grandparent

        else {

            node->is_red = false;
            grandparent_node->is_red = true;

            rotate_left(parent_node);
            rotate_right(grandparent_node);

            result.rotations++;
        }
    }

    // parent is right child of grandparent=============================
    else {

        // RR case ========================
        // node is outside grandparent

        if (node == parent_node->right) {

            parent_node->is_red = false;
            grandparent_node->is_red = true;

            rotate_left(grandparent_node);

            result.rotations++;
        }

        // RL case ==============================
        // node is inside grandparent

        else {
            node->is_red = false;
            grandparent_node->is_red = true;

            rotate_right(parent_node);
            rotate_left(grandparent_node);

            result.rotations++;
        }
    }
}
// ==============================================================
// ROTATIONS
//===============================================================
// LEFT ROTATION
// right child moves up, current node goes left 
void RedBlackTree::rotate_left(RBNode* node) {

    RBNode* right_child = node->right;
    RBNode* middle_subtree = right_child->left;

    right_child->left = node;
    node->right = middle_subtree;

    // update parent of middle subtree
    if (middle_subtree != nullptr) {
        middle_subtree->parent = node;
    }

    // connect right_child to old parent of node
    right_child->parent = node->parent;

    //Case 1: node was root: right_child becomes root
    if (node->parent == nullptr) {
        root = right_child;
    }
    // Case 2: node was left child:  update parent's left
    else if (node == node->parent->left) {
        node->parent->left = right_child;
    }
    // Case 3: node was right child: update parent's right
    else {
        node->parent->right = right_child;
    }
    // node is now child of right_child
    node->parent = right_child;
}

// RIGHT ROTATION
// left child moves up, current node goes down right 
void RedBlackTree::rotate_right(RBNode* node) {

    RBNode* left_child = node->left;
    RBNode* middle_subtree = left_child->right;

    left_child->right = node;
    node->left = middle_subtree;

    // update parent of middle subtree
    if (middle_subtree != nullptr) {
        middle_subtree->parent = node;
    }

    // connect left_child to old parent of node
    left_child->parent = node->parent;

    //Case 1: node was root: left_child becomes root
    if (node->parent == nullptr) {
        root = left_child;
    }
    // Case 2: node was left child:  update parent's left
    else if (node == node->parent->left) {
        node->parent->left = left_child;
    }
    // Case 3: node was right child: update parent's right
    else {
        node->parent->right = left_child;
    }
    // node is now child of left_child
    node->parent = left_child;
}