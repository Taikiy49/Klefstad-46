#ifndef BST_H
#define BST_H

#include <stack>
#include <iostream>
using namespace std;

// constexpr int NWORDS = 45;
constexpr int NWORDS = 45392;

struct Node
{
    string key;
    int value;
    Node * left, * right;
    int height;
    Node(const string & new_key, Node * new_left=nullptr, Node * new_right=nullptr)
        : key(new_key),
          value(0), // for map, BST needs both key and value, but ignore for our measurement
          left(new_left), right(new_right),
          height(1)
    { }

};

struct BST{
    Node * root;
    const string name;
    int count;
    class iterator{
        stack<Node*> nodeStack;
        Node* current;
    public:
        // Constructor
        iterator(Node* root = nullptr) : current(nullptr) {
            push_left(root);
        }

        // Increment operator
        iterator& operator++() {
            if (nodeStack.empty()) {
                current = nullptr;
                return *this;
            }

            current = nodeStack.top();
            nodeStack.pop();
            push_left(current->right);

            return *this;
        }

        // Dereference operator
        string& operator*() const {
            return current->key;
        }

        // Inequality operator
        bool operator!=(const iterator& other) const {
            return !nodeStack.empty() || current != other.current;
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
        return iterator(root);
    }

    // end() function
    iterator end() {
        return iterator(nullptr);
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
