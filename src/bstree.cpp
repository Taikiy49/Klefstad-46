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

void BSTree::insert(const string & key){
    root = insert_node(root, key);
    count++;
}

bool BSTree::find(const string & key) const{
    return find_node(root, key) != nullptr;
}

void BSTree::remove(const string & key){
    root = delete_node(root, key);
    count--;
}

bool BSTree::is_empty() const{
    return root == nullptr;
}

int BSTree::get_height() const{
    return compute_height(root);
}

