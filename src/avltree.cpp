#include <iostream>
#include <fstream>
#include "avltree.h"
#include <stack>
using namespace std;

// constructor
AVLTree::AVLTree()
    : BST("AVL Tree") {}

int AVLTree::get_height(Node *node) {
    if (node == nullptr) return 0;
    return node->height;
}

int AVLTree::get_balance(Node *node) {
    if (node == nullptr) return 0;
    return get_height(node->left) - get_height(node->right);
}

void AVLTree::set_height(Node *node) {
    if (node == nullptr) return;
    node->height = 1 + max(get_height(node->left), get_height(node->right));
}

Node *AVLTree::right_rotate(Node *y) {
    Node *x = y->left;
    Node *T = x->right;
    x->right = y;
    y->left = T;
    set_height(y);
    set_height(x);
    return x;
}

Node *AVLTree::left_rotate(Node *x) {
    Node *y = x->right;
    Node *T = y->left;
    y->left = x;
    x->right = T;
    set_height(x);
    set_height(y);
    return y;
}

Node *AVLTree::rebalance(Node *t) {
    stack<Node*> nodes;
    nodes.push(t);

    while (!nodes.empty()) {
        Node *current = nodes.top();
        nodes.pop();
        set_height(current);
        int balance = get_balance(current);

        if (balance > 1) {
            if (get_balance(current->left) < 0)
                current->left = left_rotate(current->left);
            current = right_rotate(current);
        } else if (balance < -1) {
            if (get_balance(current->right) > 0)
                current->right = right_rotate(current->right);
            current = left_rotate(current);
        }

        if (current->left != nullptr) nodes.push(current->left);
        if (current->right != nullptr) nodes.push(current->right);
    }

    return t;
}

Node *AVLTree::insert_node(Node *t, string key) {
    if (t == nullptr) return new Node(key);

    stack<Node*> parents;
    Node *current = t;
    while (current != nullptr) {
        parents.push(current);
        if (key < current->key)
            current = current->left;
        else if (key > current->key)
            current = current->right;
        else
            return t;
    }

    Node *newNode = new Node(key);
    if (key < parents.top()->key)
        parents.top()->left = newNode;
    else
        parents.top()->right = newNode;

    while (!parents.empty()) {
        current = parents.top();
        parents.pop();
        set_height(current);
        t = rebalance(current);
    }

    return t;
}

Node *AVLTree::find_node(Node *t, string key) {
    Node *current = t;
    while (current != nullptr && current->key != key) {
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }
    return current;
}

Node *left_most(Node *t) {
    while (t->left != nullptr) {
        t = t->left;
    }
    return t;
}

Node *AVLTree::delete_node(Node *t, string key) {
    if (t == nullptr) return nullptr;

    stack<Node*> parents;
    Node *current = t;
    while (current != nullptr && current->key != key) {
        parents.push(current);
        if (key < current->key)
            current = current->left;
        else
            current = current->right;
    }

    if (current == nullptr) return t;

    Node *child = nullptr;
    if (current->left == nullptr || current->right == nullptr) {
        child = current->left ? current->left : current->right;
        if (child == nullptr) {
            child = current;
            current = nullptr;
        } else {
            *current = *child;
            delete child;
        }
    } else {
        Node *succ = left_most(current->right);
        swap(current->key, succ->key);
        child = current->right;
    }

    while (!parents.empty()) {
        current = parents.top();
        parents.pop();
        set_height(current);
        t = rebalance(current);
    }

    return t;
}

void AVLTree::insert(const string &key) {
    root = insert_node(root, key);
    count++;
}

bool AVLTree::find(const string &key) const {
    return find_node(root, key) != nullptr;
}

void AVLTree::remove(const string &key) {
    if (find(key)) {
        root = delete_node(root, key);
        count--;
    }
}

bool AVLTree::is_empty() const {
    return root == nullptr;
}

int AVLTree::get_height() const {
    return get_height(root);
}
