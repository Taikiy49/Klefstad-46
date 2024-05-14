#include "avltree.h"
#include <iostream>
#include <string>
#include <algorithm> // this will be needed for max!
using namespace std;

// constructor
AVLTree::AVLTree()
    : BST("AVLTree") {}

int AVLTree::get_height(Node * node){
    return node ? node->height : 0;
}

int AVLTree::get_balance(Node * node){
    return node ? get_height(node->left) - get_height(node->right) : 0;
}

void AVLTree::set_height(Node * node){
    node->height = 1 + max(get_height(node->left), get_height(node->right));
}

Node * AVLTree::right_rotate(Node * y){
    Node * x = y->left;
    Node * T = x->right;
    x->right = y;
    y->left = T;
    set_height(x);
    set_height(y);
    return x;
}

Node * AVLTree::left_rotate(Node * x){
    Node * y = x->right;
    Node * T = y->left;
    y->left = x;
    x->right = T;
    set_height(x);
    set_height(y);
    return y;
}

Node * AVLTree::rebalance(Node * t){}

Node * AVLTree::insert_node(Node * t, string key){}

Node * AVLTree::find_node(Node * t, string key){}

Node * AVLTree::delete_node(Node * t, string key){}

void AVLTree::insert(const string & key){
    root = insert_node(root, key);
    count++;
}

bool AVLTree::find(const string & key) const{
    return find_node(root, key) != nullptr;
}

void AVLTree::remove(const string & key){
    root = delete_node(root, key);
    count--;
}

bool AVLTree::is_empty() const{
    return root == nullptr;
}

int AVLTree::get_height() const{
    return get_height(root);
}
