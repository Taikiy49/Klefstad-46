#include "bstree.h"
#include <iostream>
using namespace std;

BSTree::BSTree()
    : BST("BSTree") { root = nullptr; }

Node * BSTree::insert_node(Node * t, string key){}
Node * BSTree::find_node(Node * t, string key){}
Node * BSTree::left_most(Node * t){}
Node * BSTree::delete_node(Node * t, string key){}
int BSTree::compute_height(Node * t){}

void BSTree::insert(const string & key){}
bool BSTree::find(const string & key) const{}
void BSTree::remove(const string & key){}
bool BSTree::is_empty() const{}
int BSTree::get_height() const{}

