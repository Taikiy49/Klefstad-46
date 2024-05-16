#ifndef BST_H
#define BST_H

#include <stack>
#include <iostream>
using namespace std;

// constexpr int NWORDS = 45;
constexpr int NWORDS = 45392;

struct Node {
    string key;
    int value;
    Node* left;
    Node* right;
    int height;

    Node(const string& new_key, Node* new_left = nullptr, Node* new_right = nullptr)
        : key(new_key), value(1), // Initialize value to 1 to represent the node itself
          left(new_left), right(new_right), height(1) { }

    int size() const {
        return value;
    }

    void update_size() {
        value = 1 + (left ? left->size() : 0) + (right ? right->size() : 0);
    }
};

struct BST{
    Node * root;
    const string name;
    int count;
    class iterator{
        stack<Node*> nodeStack;
        Node* current;
        const BST* tree; // Pointer to the BST object

    public:
        // Constructor
        iterator(Node* root = nullptr, const BST* bst = nullptr) : current(nullptr), tree(bst) {
            push_left(root);
        }

        // Increment operator
        iterator& operator++() {
            if (current == nullptr) return *this;

            if (current->right) {
                push_left(current->right);
            }

            if (!nodeStack.empty()) {
                current = nodeStack.top();
                nodeStack.pop();
            } else {
                current = nullptr;
            }

            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            ++(*this);
            return temp;
        }

        // Dereference operator
        string& operator*() const {
            return current->key;
        }

        // Inequality operator
        bool operator!=(const iterator& other) const {
            return current != other.current;
        }

        bool operator==(const iterator& other) const {
            return current == other.current;
        }

        Node* operator->() const {
            return current->key;
        }

        // Size function
        int size() const {
            if (tree == nullptr) {
                return 0;
            }
            return tree->count; // Access count from BST object
        }

    private:
        // Helper function to push left nodes onto stack
        void push_left(Node* node) {
            while (node != nullptr) {
                nodeStack.push(node);
                node = node->left;
            }
        }
    };

    // Other members...

    // begin() function
    iterator begin() {
        return iterator(root, this); // Pass 'this' pointer to iterator
    }

    // end() function
    iterator end() {
        return iterator(nullptr, this); // Pass 'this' pointer to iterator
    }

    BST(const string & new_name)
        : root(nullptr), name(new_name), count(0) { }

    virtual void insert( const string & word) = 0;
    virtual bool find( const string & word ) const = 0;
    virtual void remove( const string & word ) = 0;

    virtual bool is_empty() const = 0;
    virtual int size() const { return count; }
    virtual int get_height() const = 0;

    static void pre_order_print(ostream & out, Node * t);
    static void in_order_print(ostream & out, Node * t);
    static void post_order_print(ostream & out, Node * t);
    static void free_tree(Node * t);
    
    void print(ostream & out) const
    {
        // pre_order_print(out, root);
        in_order_print(out, root);
        // post_order_print(out, root);
    }

    virtual ~BST(); // must delete any Nodes in the tree pointed to by root
    BST(const BST & L) = delete;
    BST& operator =(const BST & L) = delete;
};

ostream & operator << (ostream & out, BST & L);

void error(string word, string msg);
void insert_all_words(int k, string file_name, BST & L);
void find_all_words(int k, string file_name, BST & L);
void remove_all_words(int k, string file_name, BST & L);
void measure_BST(string file_name, BST & L);
void measure_BSTs(string input_file);

#endif
