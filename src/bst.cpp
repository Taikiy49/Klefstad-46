#include <iostream>
#include <fstream>
#include <string>
#include "bst.h"
#include "timer.h"
#include "avltree.h"
#include "bstree.h"

using namespace std;

void BST::pre_order_print(ostream & out, Node * t){
    if (t != nullptr){
        out << t->key << " ";
        pre_order_print(out, t->left);
        pre_order_print(out, t->right);
    }
}

void BST::in_order_print(ostream & out, Node * t){
    if (t != nullptr){
        in_order_print(out, t->left);
        out << t->key << " ";
        in_order_print(out, t->right);
    }
}

void BST::post_order_print(ostream & out, Node * t){
    if (t != nullptr){
        post_order_print(out, t->left);
        post_order_print(out, t->right);
        out << t->key << " ";
    }
}

ostream & operator<<(ostream & out, BST & L){
    L.print(out);
    return out;
}

BST::~BST(){
    free_tree(root);
}

void BST::free_tree(Node * t){
    if (t != nullptr){
        free_tree(t->left);
        free_tree(t->right);
        delete t;
    }
}

void error(string word, string msg){
    cerr << "Error: " << word << msg << endl;
}

void insert_all_words(int k, string file_name, BST & L) {
    Timer t; 
    double eTime; 
    ifstream infile(file_name);
    if (!infile) {
        error("Unable to open input file", file_name);
        return;
    }
    string word;
    int limit = k * NWORDS / 10; 
    t.start(); 
    for (int i = 0; i < limit && infile >> word; ++i) {
        L.insert(word);
    }
    t.elapsedUserTime(eTime); 
    infile.close();
    cout << "\t\tI = " << eTime << endl; 
}

void find_all_words(int k, string file_name, BST & L){
    Timer t; 
    double eTime; 
    ifstream infile(file_name);
    string word;
    int limit = k * NWORDS / 10; 
    t.start(); 
    for (int i = 0; i < limit; ++i) {
        infile >> word;
        L.find(word);
    }
    t.elapsedUserTime(eTime); 
    infile.close();
    cout << "\t\tF = " << eTime << endl; 
}

void remove_all_words(int k, string file_name, BST & L) {
    Timer t; 
    double eTime; 
    ifstream infile(file_name);
    string word;
    int limit = k * NWORDS / 10; 
    t.start(); 
    for (int i = 0; i < limit; ++i) {
        infile >> word;
        L.remove(word);
    }
    t.elapsedUserTime(eTime); 
    infile.close();
    cout << "\t\tR = " << eTime << endl; 
}

void measure_BST(string file_name, BST & L){
    cout << L.name << endl;
    for (int K = 1; K <= 10; ++K) {
        cout << "\tK = " << K << endl;
        insert_all_words(K, file_name, L);
        find_all_words(K,file_name,L);
        remove_all_words(K, file_name, L);
        if (!L.is_empty()) {
            error(L.name, "is not empty");
            exit(0);
        }
    }
}

void measure_BSTs(string input_file){
    BSTree binarySearchTree;
    measure_BST(input_file, binarySearchTree);

    AVLTree AdelsonVelskyLandisTree;
    measure_BST(input_file, AdelsonVelskyLandisTree);

}