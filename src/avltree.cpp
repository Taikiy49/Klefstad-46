#include "avltree.h"
#include <iostream>
#include <string>
#include <algorithm> // this will be needed for max!
#include "bstree.h"
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

Node * AVLTree::rebalance(Node * t){
    int balance = get_balance(t);
    if (balance > 1){
        if (get_balance(t->left) < 0) t->left = left_rotate(t->left);
        return right_rotate(t);
    }
    if (balance < -1){
        if (get_balance(t->right) > 0) t->right = right_rotate(t->right);
        return left_rotate(t);
    }
    return t;
}

Node * AVLTree::insert_node(Node * t, string key){
    if (t==nullptr) return new Node(key);
    if (key < t->key) t->left = insert_node(t->left, key);
    else if (key > t->key) t->right = insert_node(t->right, key);
    else return t;
    set_height(t);
    return rebalance(t);
}

Node* AVLTree::find_node(Node* t, string key) {
    if (t == nullptr) return nullptr; 
    if (key == t->key) return t; 
    else if (key < t->key) return find_node(t->left, key); 
    else return find_node(t->right, key);
}


Node * left_most(Node * t){
    for(;t->left != nullptr;t = t->left){}
    return t;
}

Node * AVLTree::delete_node(Node * t, string key){
    if (!t) return t;
    if (key < t->key) t->left = delete_node(t->left, key);
    else if (key > t->key) t->right = delete_node(t->right, key);
    else{
        if (t->left == nullptr || t->right == nullptr){
            Node * child = t->left ? t->left : t->right;
            if (child == nullptr){
                child = t;
                t = nullptr;
            }
            else *t = *child;
            delete child;
        }
        else{
            Node * succ = left_most(t->right);
            swap(t->key, succ->key);
            t->right = delete_node(t->right, key);
        }

    }
    return rebalance(t);
}

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
