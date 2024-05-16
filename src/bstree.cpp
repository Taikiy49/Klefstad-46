#include "bstree.h"
#include <iostream>
#include <stack>
using namespace std;

BSTree::BSTree()
    : BST("BSTree") {
    root = nullptr;
}

Node *BSTree::insert_node(Node *t, string key) {
    if (t == nullptr) {
        return new Node(key);
    }

    Node *current = t;
    stack<Node *> nodes;

    while (current != nullptr || !nodes.empty()) {
        if (current != nullptr) {
            nodes.push(current);
            if (key < current->key)
                current = current->left;
            else if (key > current->key)
                current = current->right;
            else
                return t;
        } else {
            current = nodes.top();
            nodes.pop();
            if (key < current->key)
                current->left = new Node(key);
            else if (key > current->key)
                current->right = new Node(key);
            break;
        }
    }

    return t;
}

Node *BSTree::find_node(Node *t, string key) {
    Node *current = t;
    stack<Node *> nodes;

    while (current != nullptr || !nodes.empty()) {
        if (current != nullptr) {
            nodes.push(current);
            if (current->key == key) return current;
            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        } else {
            current = nodes.top();
            nodes.pop();
            current = current->right;
        }
    }

    return nullptr;
}

Node *BSTree::left_most(Node *t) {
    while (t->left != nullptr) {
        t = t->left;
    }
    return t;
}

Node *BSTree::delete_node(Node *t, const string key) {
    if (t == nullptr) return nullptr;

    stack<Node *> nodes;
    Node *current = t;
    Node *parent = nullptr;

    while (current != nullptr || !nodes.empty()) {
        if (current != nullptr) {
            nodes.push(current);
            if (key < current->key) {
                parent = current;
                current = current->left;
            } else if (key > current->key) {
                parent = current;
                current = current->right;
            } else {
                break;
            }
        } else {
            current = nodes.top();
            nodes.pop();
            if (key < current->key)
                current = current->left;
            else
                current = current->right;
        }
    }

    if (current == nullptr) return t;

    if (current->left == nullptr) {
        Node *temp = current->right;
        if (parent == nullptr)
            t = temp;
        else if (parent->left == current)
            parent->left = temp;
        else
            parent->right = temp;
        delete current;
    } else if (current->right == nullptr) {
        Node *temp = current->left;
        if (parent == nullptr)
            t = temp;
        else if (parent->left == current)
            parent->left = temp;
        else
            parent->right = temp;
        delete current;
    } else {
        Node *succParent = current;
        Node *succ = current->right;
        while (succ->left != nullptr) {
            succParent = succ;
            succ = succ->left;
        }
        if (succParent != current) {
            succParent->left = succ->right;
        } else {
            succParent->right = succ->right;
        }
        current->key = succ->key;
        delete succ;
    }

    return t;
}

int BSTree::compute_height(Node *t) {
    int height = 0;
    stack<pair<Node *, int>> nodes;

    Node *current = t;
    int currentHeight = 0;

    while (current != nullptr || !nodes.empty()) {
        if (current != nullptr) {
            nodes.push({current, currentHeight});
            current = current->left;
            currentHeight++;
        } else {
            auto [node, nodeHeight] = nodes.top();
            nodes.pop();
            current = node->right;
            height = max(height, nodeHeight);
        }
    }

    return height;
}

void BSTree::insert(const string &key) {
    root = insert_node(root, key);
    count++;
}

bool BSTree::find(const string &key) const {
    return find_node(root, key) != nullptr;
}

void BSTree::remove(const string &key) {
    root = delete_node(root, key);
    count--;
}

bool BSTree::is_empty() const {
    return root == nullptr;
}

int BSTree::get_height() const {
    return compute_height(root);
}
