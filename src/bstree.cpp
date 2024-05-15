#include "bstree.h"
#include <iostream>
using namespace std;

BSTree::BSTree()
    : BST("BSTree") { root = nullptr; }

Node * BSTree::insert_node(Node * t, string key){
    if (t==nullptr){
        return new Node(key);
    }
    if (key < t->key) t->left = insert_node(t->left, key);
    else if (key > t->key) t->right = insert_node(t->right, key);
    return t;
}

Node * BSTree::find_node(Node * t, string key){
    if (t==nullptr) return nullptr;
    if (t->key == key) return t;
    if (key < t->key) return find_node(t->left, key);
    else return find_node(t->right, key);
}

Node * BSTree::left_most(Node * t){
    for (;t->left != nullptr; t=t->left){}
    return t;

}

Node* BSTree::delete_node(Node* t, const string key) {
    if (t == nullptr) return nullptr; // so if a key is not found, I return nullptr.
    if (key < t->key) t->left = delete_node(t->left, key);
    else if (key > t->key) t->right = delete_node(t->right, key);
    else {
        if (t->left == nullptr) {
            Node* temp = t->right;
            delete t;
            return temp;
        } else if (t->right == nullptr) {
            Node* temp = t->left;
            delete t;
            return temp;
        }
        
        Node* succ = left_most(t->right);
        t->key = succ->key;
        t->right = delete_node(t->right, succ->key);
    }
    return t;
}


int BSTree::compute_height(Node * t){
    if (t==nullptr) return 0;
    int leftHeight = compute_height(t->left);
    int rightHeight = compute_height(t->right);
    return 1 + max(leftHeight, rightHeight);
}

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

