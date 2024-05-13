#include "avltree.h"
#include <iostream>
#include <string>
#include <algorithm> // this will be needed for max!
using namespace std;

// constructor
AVLTree::AVLTree()
    : BST("AVLTree") {}

int AVLTree::get_height(Node * node){}
int AVLTree::get_balance(Node * node){}
void AVLTree::set_height(Node * node){}
Node * AVLTree::right_rotate(Node * y){}
Node * AVLTree::left_rotate(Node * x){}
Node * AVLTree::rebalance(Node * t){}
Node * AVLTree::insert_node(Node * t, string key){}
Node * AVLTree::find_node(Node * t, string key){}
Node * AVLTree::delete_node(Node * t, string key){}

void AVLTree::insert(const string & key){}
bool AVLTree::find(const string & key) const{}
void AVLTree::remove(const string & key){}
bool AVLTree::is_empty() const{}
int AVLTree::get_height() const{}